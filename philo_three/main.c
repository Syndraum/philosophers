/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:42:19 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/15 21:25:46 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	launch_group(int nbr, t_kitchen *kitchen)
{
	int i;

	i = -1;
	while (++i < nbr)
	{
		create_thread(i, kitchen, nbr);
		if (i != nbr - 1)
			usleep(kitchen->t_to_eat / nbr);
	}
}

int		ckeck_execute(int argc, char *argv[], t_kitchen *kitchen)
{
	int i;

	sem_unlink("fork");
	sem_unlink("wait");
	sem_unlink("print");
	sem_unlink("die");
	if (argc < 5)
		return (ft_error("not enought argument (min 4)\n", 1));
	else if (argc > 6)
		return (ft_error("too much arguments (max 5)\n", 1));
	if (init_kitchen(kitchen, argc, argv))
		return (ft_error("Allocation problem\n", 2));
	i = 0;
	while (++i < argc)
	{
		if (!is_all_digit(argv[i]))
			return (ft_error("a argument isn't a possitive int\n", 3));
	}
	return (0);
}

void	waiting(t_kitchen *kitchen)
{
	int			status;
	t_list		*cursor;
	t_philo		*philo;

	waitpid(-1, &status, 0);
	if (status > 0)
	{
		cursor = kitchen->philos;
		while (cursor != 0)
		{
			philo = cursor->content;
			kill(philo->pid, SIGTERM);
			cursor = cursor->next;
		}
		return ;
	}
	else if (kitchen->remain == 1)
		return ;
	else
	{
		kitchen->remain--;
		waiting(kitchen);
	}
}

int		main(int argc, char *argv[])
{
	t_kitchen	kitchen;

	if (ckeck_execute(argc, argv, &kitchen))
		return (1);
	kitchen.sem_forks = sem_open("fork", O_CREAT, S_IRWXU, (kitchen.n_philo));
	if (kitchen.sem_forks == SEM_FAILED)
	{
		ft_putstr_fd("Error : sem_open failed\n", 2);
		return (EXIT_FAILURE);
	}
	launch_group(2, &kitchen);
	waiting(&kitchen);
	free_kitchen(&kitchen);
	return (0);
}
