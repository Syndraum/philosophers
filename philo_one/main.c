/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 14:24:16 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_philo(t_philo *philo)
{
	free(philo->s_id);
}

void	free_kitchen(t_kitchen *kitchen)
{
	int i;

	i = -1;
	while (++i < kitchen->n_philo)
		free_philo(&kitchen->philos[i]);
	free(kitchen->forks);
	free(kitchen->philos);
	free(kitchen->thread);
}

void	eat_sleep(t_philo *philo)
{
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;

	print_message(philo, TEXT_EAT);
	gettimeofday(&philo->last_eat, NULL);
	usleep(kitchen->t_to_eat);
	pthread_mutex_unlock(&kitchen->forks[philo->forks[0]]);
	pthread_mutex_unlock(&kitchen->forks[philo->forks[1]]);
	print_message(philo, TEXT_SLEEP);
	is_die(philo);
	usleep(kitchen->t_to_sleep);
	is_die(philo);
	print_message(philo, TEXT_THINK);
}

void	*philosopher(void *data)
{
	int	n;

	t_philo		*philo = (t_philo*)data;
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;
	gettimeofday(&philo->last_eat, NULL);
	n = 0;
	while (!is_finish(n, kitchen) && !is_one_died(kitchen))
	{
		if (!pthread_mutex_lock(&kitchen->forks[philo->forks[0]]))
		{
			if (!pthread_mutex_lock(&kitchen->forks[philo->forks[1]]))
				eat_sleep(philo);
			else
				pthread_mutex_unlock(&kitchen->forks[philo->forks[0]]);
		}
		n++;
		is_die(philo);
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			i;

	if (argc < 5 )
	{
		ft_putstr_fd("Number of arguemnt to low (min 5)\n", 2);
		exit(1);
	}
	if (!init_kitchen(&kitchen, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		exit(2);
	}
	i=-1;
	while (++i < kitchen.n_philo)
	{
		init_philosoph(&kitchen.philos[i], &kitchen, i + 1);
		pthread_create(&kitchen.thread[i], NULL, philosopher, &kitchen.philos[i]);
	}
	i = -1;
	while (++i < kitchen.n_philo)
		pthread_join(kitchen.thread[i], NULL);
	free_kitchen(&kitchen);
	return (0);
}
