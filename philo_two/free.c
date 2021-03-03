/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:49:13 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/03 22:18:52 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

void	free_philo(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	sem_close(philo->sem_last_eat);
	sem_unlink(philo->s_id);
	free(philo->s_id);
	free(philo);
}

void	free_kitchen(t_kitchen *kitchen)
{
	int i;

	i = -1;
	// while (++i < kitchen->n_philo)
	// 	free_philo(&kitchen->philos[i]);
	sem_close(kitchen->sem_die);
	sem_close(kitchen->sem_print);
	sem_close(kitchen->sem_wait);
	sem_unlink("die");
	sem_unlink("print");
	sem_unlink("wait");
	ft_lstclear(&kitchen->philos, free_philo);
	free(kitchen->thread);
}