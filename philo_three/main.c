/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:42:19 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/16 13:37:38 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	pid_t		pid;

	pid = waitpid(-1, &status, 0);
	if (status > 0)
	{
		cursor = kitchen->philos;
		while (cursor != 0)
		{
			philo = cursor->content;
			if (pid != philo->pid)
				kill(philo->pid, SIGKILL);
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
	create_thread(&kitchen);
	waiting(&kitchen);
	free_kitchen(&kitchen);
	return (0);
}
