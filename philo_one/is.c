/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:35:54 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 15:34:39 by roalvare         ###   ########.fr       */
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

int		is_finish(int n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == n)
		return (1);
	return (0);
}
