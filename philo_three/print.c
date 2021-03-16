/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:02:50 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/16 13:25:53 by roalvare         ###   ########.fr       */
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

int		print_message(t_philo *philo, char *text)
{
	char			*ts;
	char			*str;
	char			*tmp;

	if (is_one_died(philo->kitchen))
		return (1);
	sem_wait(philo->kitchen->sem_print);
	gettimeofday(&philo->now, NULL);
	ts = get_timestamp(&philo->kitchen->t_begin, &philo->now);
	tmp = ft_strjoin(ts, philo->s_id);
	free(ts);
	str = ft_strjoin(tmp, text);
	free(tmp);
	// if (is_one_died(philo->kitchen))
	// {
	// 	free(str);
	// 	sem_post(philo->kitchen->sem_print);
	// 	return (1);
	// }
	// else
	// 	ft_putstr_fd("NOPE\n", 1);
	ft_putstr_fd(str, 1);
	sem_post(philo->kitchen->sem_print);
	free(str);
	return (0);
}
