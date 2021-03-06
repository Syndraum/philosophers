/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:34:12 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/15 20:50:39 by roalvare         ###   ########.fr       */
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
	philo->forks[0] = &kitchen->forks[(id - 1) % kitchen->n_philo];
	philo->forks[1] = &kitchen->forks[(id) % kitchen->n_philo];
	pthread_mutex_init(&philo->m_last_eat, NULL);
	philo->kitchen = kitchen;
	gettimeofday(&philo->last_eat, NULL);
	philo->n_eat = 0;
	return (philo);
}

void	init_static_var(t_kitchen *kitchen)
{
	kitchen->philo_die = 0;
	kitchen->philo_finish = 0;
	pthread_mutex_init(&kitchen->m_die, NULL);
	pthread_mutex_init(&kitchen->m_print, NULL);
	kitchen->philos = NULL;
}

int		init_kitchen(t_kitchen *kitchen, int argc, char *argv[])
{
	int i;

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
	kitchen->forks = malloc(sizeof(pthread_mutex_t) * kitchen->n_philo);
	if (kitchen->forks == 0)
		return (2);
	i = -1;
	while (++i < kitchen->n_philo)
		pthread_mutex_init(&kitchen->forks[i], NULL);
	kitchen->thread = malloc(sizeof(pthread_t) * kitchen->n_philo);
	if (kitchen->thread == 0)
		return (2);
	gettimeofday(&kitchen->t_begin, NULL);
	return (0);
}
