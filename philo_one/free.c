/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:21:49 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/01 12:12:27 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_philo(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	free(philo->s_id);
	free(philo);
}

void	free_kitchen(t_kitchen *kitchen)
{
	int i;

	i = -1;
	while (++i < kitchen->n_philo)
		pthread_mutex_destroy(&kitchen->forks[i]);
	pthread_mutex_destroy(&kitchen->m_die);
	free(kitchen->forks);
	ft_lstclear(&kitchen->philos, free_philo);
	free(kitchen->thread);
}
