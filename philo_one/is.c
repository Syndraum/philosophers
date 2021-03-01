/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:35:54 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/01 13:30:49 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

void	set_die(t_kitchen *kitchen, t_philo *philo)
{
	pthread_mutex_lock(&kitchen->m_die);
	print_message(philo, TEXT_DIE);
	kitchen->philo_die = 1;
	pthread_mutex_unlock(&kitchen->m_die);
}

int		check_all_die(t_kitchen *kitchen)
{
	struct timeval	now;
	t_philo			*philo;
	t_list			*cursor;
	int				i;

	i = 0;
	kitchen->n_finish = 0;
	gettimeofday(&now, NULL);
	cursor = kitchen->philos;
	while (cursor)
	{
		philo = cursor->content;
		pthread_mutex_lock(&philo->m_last_eat);
		if (is_died(kitchen, &philo->last_eat, &now))
		{
			set_die(kitchen, philo);
			return (i);
		}
		pthread_mutex_unlock(&philo->m_last_eat);
		// if (is_finish(&philo->n_eat, kitchen))
		// 	kitchen->n_finish++;
		i++;
		cursor = cursor->next;
	}
	// if (kitchen->n_finish == kitchen->n_philo)
	// 	return (1);
	return (-1);
}

int		is_finish(int *n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == *n){
		(kitchen->philo_finish)++;
		return (1);
	}
	return (0);
}
