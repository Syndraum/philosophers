/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:45:33 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/15 21:43:18 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->kitchen->sem_forks);
	print_message(philo, TEXT_FORK);
	sem_wait(philo->kitchen->sem_wait);
	sem_wait(philo->kitchen->sem_forks);
	sem_post(philo->kitchen->sem_wait);
	print_message(philo, TEXT_FORK);
	gettimeofday(&philo->last_eat, NULL);
	print_message(philo, TEXT_EAT);
	my_usleep(philo->kitchen->t_to_eat, &philo->t_wake_up);
	sem_post(philo->kitchen->sem_forks);
	sem_post(philo->kitchen->sem_forks);
}

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	if (philo->id % 2 == 0)
		usleep(philo->kitchen->t_to_eat / 2);
	while (!is_finish(&philo->n_eat, philo->kitchen)
	&& !check_die(philo))
	{
		eat(philo);
		(philo->n_eat)++;
		if (is_finish(&philo->n_eat, philo->kitchen))
			return (0);
		print_message(philo, TEXT_SLEEP);
		my_usleep(philo->kitchen->t_to_sleep, &philo->t_wake_up);
		print_message(philo, TEXT_THINK);
	}
	if (philo->kitchen->philo_die)
		exit(1);
	return (0);
}

void	create_thread(t_kitchen *kitchen)
{
	t_philo	*philo;
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < kitchen->n_philo)
	{
		philo = init_philosoph(kitchen, i + 1);
		ft_lstadd_back(&kitchen->philos, ft_lstnew(philo));
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			pthread_create(&kitchen->thread[i], 0, philosopher, philo);
			pthread_detach(kitchen->thread[i]);
			while (!check_die(philo) && !kitchen->philo_finish)
				usleep(50);
			free_kitchen(kitchen);
			exit(0);
		}
		else
			philo->pid = pid;
	}
}
