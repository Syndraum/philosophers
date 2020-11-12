/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:21:49 by roalvare          #+#    #+#             */
/*   Updated: 2020/11/12 17:27:23 by roalvare         ###   ########.fr       */
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
	free(kitchen->forks);
	ft_lstclear(&kitchen->philos, free_philo);
	free(kitchen->thread);
}
