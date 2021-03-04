/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:54:28 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/04 10:58:32 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	while (!is_finish(&philo->n_eat, philo->kitchen)
	&& !is_one_died(philo->kitchen))
	{
		sem_wait(philo->kitchen->sem_forks);
		print_message(philo, TEXT_FORK);
		sem_wait(philo->kitchen->sem_wait);
		sem_wait(philo->kitchen->sem_forks);
		sem_post(philo->kitchen->sem_wait);
		print_message(philo, TEXT_FORK);
		print_message(philo, TEXT_EAT);
		gettimeofday(&philo->last_eat, NULL);
		my_usleep(philo->kitchen->t_to_eat, &philo->t_wake_up);
		sem_post(philo->kitchen->sem_forks);
		sem_post(philo->kitchen->sem_forks);
		(philo->n_eat)++;
		if (is_finish(&philo->n_eat, philo->kitchen))
			return (0);
		print_message(philo, TEXT_SLEEP);
		my_usleep(philo->kitchen->t_to_sleep, &philo->t_wake_up);
		print_message(philo, TEXT_THINK);
	}
	return (0);
}

void	create_thread(int i, t_kitchen *kitchen, int inc)
{
	t_philo		*philo;

	while (i < kitchen->n_philo)
	{
		philo = init_philosoph(kitchen, i + 1);
		ft_lstadd_back(&kitchen->philos, ft_lstnew(philo));
		pthread_create(&kitchen->thread[i], 0, philosopher, philo);
		i += inc;
	}
}

void	launch_group(int nbr, t_kitchen *kitchen)
{
	int i;

	i = -1;
	while (++i < nbr)
	{
		create_thread(i, kitchen, nbr);
		if (i != nbr - 1)
			usleep(kitchen->t_to_eat / nbr);
	}
}

int		ckeck_execute(int argc, char const *argv[], t_kitchen *kitchen)
{
	sem_unlink("fork");
	sem_unlink("wait");
	sem_unlink("print");
	sem_unlink("die");
	if (argc < 5)
	{
		ft_putstr_fd("Number of arguemnt too low (min 5)\n", 2);
		return (1);
	}
	if (init_kitchen(kitchen, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		return (2);
	}
	return (0);
}

int		main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			i;

	if (ckeck_execute(argc, argv, &kitchen))
		return (1);
	kitchen.sem_forks = sem_open("fork", O_CREAT, S_IRWXU, (kitchen.n_philo));
	if (kitchen.sem_forks == SEM_FAILED)
	{
		ft_putstr_fd("Error : sem_open failed\n", 2);
		return (EXIT_FAILURE);
	}
	launch_group(2, &kitchen);
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
