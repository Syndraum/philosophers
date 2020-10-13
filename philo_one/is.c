/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:35:54 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/13 14:40:06 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

int		is_die(t_philo *philo)
{
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;
	struct timeval	current;
	long		diff;

	gettimeofday(&current, NULL);
	diff = diff_timestamp(&philo->last_eat, &current);
	if (diff >= kitchen->t_to_die)
	{
		kitchen->philo_die = 1;
		print_message(philo, TEXT_DIE);
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