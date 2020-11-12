/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:35:54 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 14:26:49 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

int		check_all_die(t_kitchen *kitchen)
{
	struct timeval	now;
	t_philo			*philo;
	t_list			*cursor;

	kitchen->n_finish = 0;
	gettimeofday(&now, NULL);
	cursor = kitchen->philos;
	while(cursor)
	{
		philo = cursor->content;
		if (is_died(kitchen, &philo->last_eat, &now))
		{
			pthread_mutex_lock(&kitchen->m_die);
			print_message(philo, TEXT_DIE);
			kitchen->philo_die = 1;
			pthread_mutex_unlock(&kitchen->m_die);
			return (1);
		}
		if (is_finish(&philo->n_eat, kitchen))
			kitchen->n_finish++;
		cursor = cursor->next;
	}
	if (kitchen->n_finish == kitchen->n_philo)
		return (1);
	return (0);
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
		pthread_mutex_lock(&kitchen->m_die);
		print_message(philo, TEXT_DIE);
		kitchen->philo_die = 1;
		pthread_mutex_unlock(&kitchen->m_die);
		return (1);
		
	}
	return (0);
}

int		is_finish(int *n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == *n)
		return (1);
	return (0);
}
