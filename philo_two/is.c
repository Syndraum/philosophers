/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:32:50 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/02 22:10:29 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

int		is_die(t_philo *philo)
{
	t_kitchen		*kitchen;
	long			diff;

	kitchen = (t_kitchen*)philo->kitchen;
	gettimeofday(&philo->now, NULL);
	diff = diff_timestamp(&philo->last_eat, &philo->now);
	if (diff > kitchen->t_to_die)
	{
		print_message(philo, TEXT_DIE);
		kitchen->philo_die = 1;
		return (1);
	}
	return (0);
}

void	set_die(t_kitchen *kitchen, t_philo *philo)
{
	sem_wait(kitchen->sem_die);
	print_message(philo, TEXT_DIE);
	kitchen->philo_die = 1;
	sem_post(kitchen->sem_die);
}

int		check_all_die(t_kitchen *kitchen)
{
	struct timeval	now;
	t_philo			*philo;
	t_list			*cursor;

	gettimeofday(&now, NULL);
	cursor = kitchen->philos;
	while (cursor)
	{
		philo = cursor->content;
		sem_wait(philo->sem_last_eat);
		if (is_died(kitchen, &philo->last_eat, &now))
		{
			set_die(kitchen, philo);
			sem_post(philo->sem_last_eat);
			return (1);
		}
		sem_post(philo->sem_last_eat);
		cursor = cursor->next;
	}
	return (0);
}

int		is_finish(int *n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == *n)
	{
		(kitchen->philo_finish)++;
		return (1);
	}
	return (0);
}
