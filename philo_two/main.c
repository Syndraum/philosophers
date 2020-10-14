/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:54:28 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 18:59:25 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	return 0;
}

int main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			i;

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
	i = -1;
	while (++i < kitchen.n_philo)
	{
		init_philosoph(&kitchen.philos[i], &kitchen, i + 1);
		pthread_create(&kitchen.thread[i], 0, philosopher, &kitchen.philos[i]);
		kitchen.sem[i] = sem_open(kitchen.philos[i].s_id, O_CREAT, S_IRWXU, 0);
		if (kitchen.sem[i] == SEM_FAILED)
		{
			ft_putstr_fd("Error : sem_open failed\n", 2);
			return (EXIT_FAILURE);
		}
		
	}
	i = -1;
	while (++i < kitchen.n_philo)
	{
		sem_close(kitchen.sem[i]);
		sem_unlink(kitchen.philos[i].s_id);
	}
	return 0;
}
