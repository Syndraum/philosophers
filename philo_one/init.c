/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:34:12 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/16 17:43:43 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_philosoph(t_philo *philo, t_kitchen *kitchen, int id)
{
	char	*tmp;

	philo->id = id;
	tmp = ft_itoa(philo->id);
	philo->s_id = ft_strjoin(" ", tmp);
	free(tmp);
	philo->forks[0] = (id - 1) % kitchen->n_philo;
	philo->forks[1] = (id) % kitchen->n_philo;
	philo->kitchen = kitchen;
	gettimeofday(&philo->last_eat, NULL);
}

int		init_kitchen(t_kitchen *kitchen, int argc, char const *argv[])
{
	int i;

	kitchen->philo_die = 0;
	pthread_mutex_init(&kitchen->m_die, NULL);
	kitchen->n_must_eat = -1;
	kitchen->n_philo = ft_atoi(argv[1]);
	kitchen->t_to_die = ft_atoi(argv[2]) * 1000;
	kitchen->t_to_eat = ft_atoi(argv[3]) * 1000;
	kitchen->t_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc > 5)
		kitchen->n_must_eat = ft_atoi(argv[5]);
	kitchen->forks = malloc(sizeof(pthread_mutex_t) * kitchen->n_philo);
	if (kitchen->forks == 0)
		return (0);
	i = -1;
	while (++i < kitchen->n_philo)
		pthread_mutex_init(&kitchen->forks[i], NULL);
	kitchen->thread = malloc(sizeof(pthread_t) * kitchen->n_philo);
	if (kitchen->thread == 0)
		return (0);
	kitchen->philos = malloc(sizeof(t_philo) * kitchen->n_philo);
	if (kitchen->philos == 0)
		return (0);
	gettimeofday(&kitchen->t_begin, NULL);
	return (1);
}
