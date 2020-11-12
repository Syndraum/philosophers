/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 16:56:58 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_philo(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	free(philo->s_id);
	free(philo);
}

void	free_kitchen(t_kitchen *kitchen)
{
	free(kitchen->forks);
	ft_lstclear(&kitchen->philos, free_philo);
	free(kitchen->thread);
}

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
	while (!is_finish(&philo->n_eat, philo->kitchen) && !is_one_died(philo->kitchen))
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

int		main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	t_philo		*philo;
	int			i;

	if (argc < 5)
	{
		ft_putstr_fd("Number of arguemnt to low (min 5)\n", 2);
		exit(1);
	}
	if (!init_kitchen(&kitchen, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		exit(2);
	}
	i = 0;
	while (i < kitchen.n_philo)
	{
		philo = init_philosoph(&kitchen, i + 1);
		ft_lstadd_back(&kitchen.philos, ft_lstnew(philo));
		pthread_create(&kitchen.thread[i], 0, philosopher, philo);
		pthread_detach(kitchen.thread[i]);
		i += 2;
	}
	i = 1;
	usleep(kitchen.t_to_eat / 2);
	while (i < kitchen.n_philo)
	{
		philo = init_philosoph(&kitchen, i + 1);
		ft_lstadd_back(&kitchen.philos, ft_lstnew(philo));
		pthread_create(&kitchen.thread[i], 0, philosopher, philo);
		pthread_detach(kitchen.thread[i]);
		i += 2;
	}
	while (!check_all_die(&kitchen))
		usleep(50);
	// i = -1;
	// while (++i < kitchen.n_philo)
	// 	pthread_join(kitchen.thread[i], NULL);
	free_kitchen(&kitchen);
	// ft_putstr_fd("END\n", 2);
	return (0);
}
