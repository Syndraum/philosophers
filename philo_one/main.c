/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/22 17:47:59 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_philo(t_philo *philo)
{
	free(philo->s_id);
}

void	free_kitchen(t_kitchen *kitchen)
{
	// int i;

	// i = -1;
	// while (++i < kitchen->n_philo)
	// 	free_philo(&kitchen->philos[i]);
	free(kitchen->forks);
	// free(kitchen->philos);
	free(kitchen->thread);
}

int		eat_sleep(t_philo *philo)
{
	print_message(philo, TEXT_EAT);
	gettimeofday(&philo->last_eat, NULL);
	usleep(philo->kitchen->t_to_eat);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	print_message(philo, TEXT_SLEEP);
	usleep(philo->kitchen->t_to_sleep);
	print_message(philo, TEXT_THINK);
	return (0);
}

void	*philosopher(void *data)
{
	int			n;
	t_philo		*philo;

	philo = (t_philo*)data;
	n = 0;
	while (!is_finish(n, philo->kitchen) && !is_one_died(philo->kitchen))
	{
		pthread_mutex_lock(philo->forks[0]);
		print_message(philo, TEXT_FORK);
		pthread_mutex_lock(philo->forks[1]);
		print_message(philo, TEXT_FORK);
		if (eat_sleep(philo))
			return (0);
		n++;
	}
	return (0);
}

void	*check_die(void *data){
	t_philo		*philo;

	philo = (t_philo*)data;
	gettimeofday(&philo->last_eat, NULL);
	pthread_create(&philo->thread, 0, philosopher, philo);
	while(!is_die(philo))
		;
	exit (0);
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
		pthread_create(&kitchen.thread[i], 0, check_die, philo);
		i += 2;
	}
	i = 1;
	usleep(kitchen.t_to_eat / 2);
	while (i < kitchen.n_philo)
	{
		philo = init_philosoph(&kitchen, i + 1);
		ft_lstadd_back(&kitchen.philos, ft_lstnew(philo));
		pthread_create(&kitchen.thread[i], 0, check_die, philo);
		i += 2;
	}
	i = -1;
	while (++i < kitchen.n_philo)
		pthread_join(kitchen.thread[i], NULL);
	free_kitchen(&kitchen);
	return (0);
}
