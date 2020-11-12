/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:44:59 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 17:21:09 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putstr_fd(char *s, int fd)
{
	int len;

	if (s != NULL)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}

void	print_message(t_philo *philo, char *text)
{
	char			*ts;
	char			*str;
	char			*tmp;

	gettimeofday(&philo->now, NULL);
	ts = get_timestamp(&philo->kitchen->t_begin, &philo->now);
	tmp = ft_strjoin(ts, philo->s_id);
	free(ts);
	str = ft_strjoin(tmp, text);
	free(tmp);
	if (is_one_died(philo->kitchen))
	{
		free(str);
		exit(0);
	}
	ft_putstr_fd(str, 1);
	free(str);
}
