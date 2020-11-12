/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 17:21:57 by roalvare         ###   ########.fr       */
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

void	create_trhead(int *i, t_kitchen *kitchen)
{
	t_philo		*philo;

	while (*i < kitchen->n_philo)
	{
		philo = init_philosoph(kitchen, *i + 1);
		ft_lstadd_back(&kitchen->philos, ft_lstnew(philo));
		pthread_create(&kitchen->thread[*i], 0, philosopher, philo);
		pthread_detach(kitchen->thread[*i]);
		*i += 2;
	}
}

int		main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
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
	create_trhead(&i, &kitchen);
	i = 1;
	usleep(kitchen.t_to_eat / 2);
	create_trhead(&i, &kitchen);
	while (!check_all_die(&kitchen))
		usleep(50);
	free_kitchen(&kitchen);
	return (0);
}
