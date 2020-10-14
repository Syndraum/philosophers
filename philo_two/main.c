/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:54:28 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 20:52:35 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_philo(t_philo *philo)
{
	free(philo->s_id);
}

void	free_kitchen(t_kitchen *kitchen)
{
	int i;

	i = -1;
	while (++i < kitchen->n_philo)
		free_philo(&kitchen->philos[i]);
	free(kitchen->philos);
	free(kitchen->thread);
}

void	*philosopher(void *data)
{
	int			n;
	t_philo		*philo;
	t_kitchen	*kitchen;

	philo = (t_philo*)data;
	kitchen = (t_kitchen*)philo->kitchen;
	gettimeofday(&philo->last_eat, NULL);
	n = 0;
	while (!is_finish(n, kitchen) && !is_one_died(kitchen) && !is_die(philo))
	{
		sem_wait(kitchen->sem);
		print_message(philo, TEXT_EAT);
		usleep(kitchen->t_to_eat);
		sem_post(kitchen->sem);
		if (is_die(philo))
			return (0);
		print_message(philo, TEXT_SLEEP);
		usleep(kitchen->t_to_sleep);
		if (is_die(philo))
			return (0);
		print_message(philo, TEXT_THINK);
		n++;
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			i;

	sem_close(kitchen.sem);
	sem_unlink("fork");
	if (argc < 5)
	{
		ft_putstr_fd("Number of arguemnt to low (min 5)\n", 2);
		exit(1);
	}
	if (!init_kitchen(&kitchen, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		exit(2);
	}
	kitchen.sem = sem_open("fork", O_CREAT, S_IRWXU, (kitchen.n_philo / 2));
	if (kitchen.sem == SEM_FAILED)
	{
		ft_putstr_fd("Error : sem_open failed\n", 2);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < kitchen.n_philo)
	{
		init_philosoph(&kitchen.philos[i], &kitchen, i + 1);
		pthread_create(&kitchen.thread[i], 0, philosopher, &kitchen.philos[i]);
	}
	i = -1;
	while (++i < kitchen.n_philo)
		pthread_join(kitchen.thread[i], NULL);
	i = -1;
	while (++i < kitchen.n_philo)
	{
		sem_close(kitchen.sem);
		sem_unlink("fork");
	}
	free_kitchen(&kitchen);
	return 0;
}
