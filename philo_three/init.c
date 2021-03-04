/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:39:06 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/04 13:44:15 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*init_philosoph(t_kitchen *kitchen, int id)
{
	char	*tmp;
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (0);
	philo->id = id;
	tmp = ft_itoa(philo->id);
	philo->s_id = ft_strjoin(" ", tmp);
	free(tmp);
	philo->kitchen = kitchen;
	sem_unlink(philo->s_id);
	philo->sem_last_eat = sem_open(philo->s_id, O_CREAT, S_IRWXU, 1);
	if (philo->sem_last_eat == SEM_FAILED)
		return (0);
	gettimeofday(&philo->last_eat, NULL);
	philo->n_eat = 0;
	philo->pid = -1;
	return (philo);
}

void	init_static_var(t_kitchen *kitchen)
{
	kitchen->philo_finish = 0;
	kitchen->sem_die = sem_open("die", O_CREAT, S_IRWXU, 1);
	kitchen->sem_print = sem_open("print", O_CREAT, S_IRWXU, 1);
	kitchen->sem_wait = sem_open("wait", O_CREAT, S_IRWXU, 1);
	kitchen->philos = NULL;
}

int		init_kitchen(t_kitchen *kitchen, int argc, char const *argv[])
{
	kitchen->n_philo = ft_atoi(argv[1]);
	if (kitchen->n_philo <= 0)
		return (1);
	init_static_var(kitchen);
	kitchen->t_to_die = ft_atoi(argv[2]) * 1000;
	kitchen->t_to_eat = ft_atoi(argv[3]) * 1000;
	kitchen->t_to_sleep = ft_atoi(argv[4]) * 1000;
	kitchen->n_must_eat = -1;
	if (argc > 5)
		kitchen->n_must_eat = ft_atoi(argv[5]);
	kitchen->thread = malloc(sizeof(pthread_t) * kitchen->n_philo);
	if (kitchen->thread == 0)
		return (2);
	kitchen->philo_die = malloc(sizeof(char));
	if (kitchen->philo_die == 0)
		return (2);
	*(kitchen->philo_die) = 0;
	gettimeofday(&kitchen->t_begin, NULL);
	return (0);
}
