/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:54:28 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/15 21:10:52 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		eat_sleep(t_philo *philo)
{
	print_message(philo, TEXT_EAT);
	gettimeofday(&philo->last_eat, NULL);
	my_usleep(philo->kitchen->t_to_eat, &philo->t_wake_up);
	sem_post(philo->kitchen->sem_forks);
	sem_post(philo->kitchen->sem_forks);
	(philo->n_eat)++;
	if (is_finish(&philo->n_eat, philo->kitchen))
		return (1);
	print_message(philo, TEXT_SLEEP);
	my_usleep(philo->kitchen->t_to_sleep, &philo->t_wake_up);
	print_message(philo, TEXT_THINK);
	return (0);
}

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	if (philo->id % 2 == 0)
		usleep(philo->kitchen->t_to_eat / 2);
	while (!is_finish(&philo->n_eat, philo->kitchen)
	&& !is_one_died(philo->kitchen))
	{
		sem_wait(philo->kitchen->sem_forks);
		print_message(philo, TEXT_FORK);
		sem_wait(philo->kitchen->sem_wait);
		sem_wait(philo->kitchen->sem_forks);
		sem_post(philo->kitchen->sem_wait);
		print_message(philo, TEXT_FORK);
		if (eat_sleep(philo))
			return (0);
	}
	return (0);
}

void	create_thread(t_kitchen *kitchen)
{
	t_philo		*philo;
	int		i;

	i = -1;
	while (++i < kitchen->n_philo)
	{
		philo = init_philosoph(kitchen, i + 1);
		ft_lstadd_back(&kitchen->philos, ft_lstnew(philo));
		pthread_create(&kitchen->thread[i], 0, philosopher, philo);
	}
}

int		ckeck_execute(int argc, char *argv[], t_kitchen *kitchen)
{
	int i;

	sem_unlink("fork");
	sem_unlink("wait");
	sem_unlink("print");
	sem_unlink("die");
	if (argc < 5)
		return (ft_error("not enought argument (min 4)\n", 1));
	else if (argc > 6)
		return (ft_error("too much arguments (max 5)\n", 1));
	if (init_kitchen(kitchen, argc, argv))
		return (ft_error("Allocation problem\n", 2));
	i = 0;
	while (++i < argc)
	{
		if (!is_all_digit(argv[i]))
			return (ft_error("a argument isn't a possitive int\n", 3));
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_kitchen	kitchen;
	int			i;

	if (ckeck_execute(argc, argv, &kitchen))
		return (1);
	kitchen.sem_forks = sem_open("fork", O_CREAT, S_IRWXU, (kitchen.n_philo));
	if (kitchen.sem_forks == SEM_FAILED)
		return (ft_error("sem_open failed\n", EXIT_FAILURE));
	create_thread(&kitchen);
	while (!check_all_die(&kitchen) && !kitchen.philo_finish)
		usleep(50);
	i = -1;
	while (++i < kitchen.n_philo)
	{
		sem_post(kitchen.sem_wait);
		sem_post(kitchen.sem_forks);
		pthread_join(kitchen.thread[i], NULL);
	}
	free_kitchen(&kitchen);
	return (0);
}
