/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:35:54 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 14:44:47 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

void	is_die(t_philo *philo)
{
	t_kitchen		*kitchen;
	struct timeval	current;
	long			diff;

	kitchen = (t_kitchen*)philo->kitchen;
	gettimeofday(&current, NULL);
	diff = diff_timestamp(&philo->last_eat, &current);
	if (diff > kitchen->t_to_die)
	{
		print_message(philo, TEXT_DIE);
		kitchen->philo_die = 1;
		exit(1);
	}
}

int		is_finish(int n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == n)
		return (1);
	return (0);
}
