/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/15 20:52:22 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		eat_sleep(t_philo *philo)
{
	print_message(philo, TEXT_EAT);
	pthread_mutex_lock(&philo->m_last_eat);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->m_last_eat);
	my_usleep(philo->kitchen->t_to_eat, &philo->t_wake_up);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
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
		pthread_mutex_lock(philo->forks[0]);
		print_message(philo, TEXT_FORK);
		pthread_mutex_lock(philo->forks[1]);
		print_message(philo, TEXT_FORK);
		if (eat_sleep(philo))
			return (0);
	}
	return (0);
}

void	create_thread(t_kitchen *kitchen)
{
	t_philo	*philo;
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
	create_thread(&kitchen);
	while (!check_all_die(&kitchen) && !kitchen.philo_finish)
		usleep(50);
	i = -1;
	while (++i < kitchen.n_philo)
	{
		pthread_mutex_unlock(&kitchen.forks[i]);
		pthread_join(kitchen.thread[i], NULL);
	}
	free_kitchen(&kitchen);
	return (0);
}
