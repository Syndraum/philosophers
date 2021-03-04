/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:49:13 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/04 10:55:56 by roalvare         ###   ########.fr       */
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
	sem_close(kitchen->sem_forks);
	sem_unlink("fork");
	sem_close(kitchen->sem_die);
	sem_close(kitchen->sem_print);
	sem_close(kitchen->sem_wait);
	sem_unlink("die");
	sem_unlink("print");
	sem_unlink("wait");
	ft_lstclear(&kitchen->philos, free_philo);
	free(kitchen->thread);
}
