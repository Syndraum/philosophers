/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:39:03 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 14:44:59 by roalvare         ###   ########.fr       */
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
	char	*ts;
	char	*tmp;
	long	diff;

	diff = diff_timestamp(begin, current) / 1000;
	tmp = ft_itoa(diff);
	ts = ft_strjoin(tmp, "ms ");
	free(tmp);
	if (ts == 0)
		return (0);
	return (ts);
}
