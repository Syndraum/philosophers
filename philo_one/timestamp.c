/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:39:03 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 14:55:29 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	diff_timestamp(struct timeval *begin, struct timeval *end)
{
	long	diff;

	diff = end->tv_sec * 1000000 + end->tv_usec;
	diff -= begin->tv_sec * 1000000 + begin->tv_usec;
	return (diff);
}

char	*get_timestamp(struct timeval *begin, struct timeval *current)
{
	return (ft_itoa(diff_timestamp(begin, current) / 1000));
}

int		is_died(t_kitchen *kitchen, struct timeval *begin, struct timeval *end)
{
	if (diff_timestamp(begin, end) > kitchen->t_to_die)
		return (1);
	return (0);
}

void	set_time(struct timeval *time, int time_add)
{
	gettimeofday(&time, NULL);
	time->tv_usec += time_add;
	while (time->tv_usec >= 1000000)
	{
		time->tv_sec++;
		time->tv_usec -= 1000000;
	}
}

void	my_usleep(struct timeval *t_wake_up)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (diff_timestamp(&now, t_wake_up) > 0)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
}