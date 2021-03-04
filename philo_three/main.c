/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:42:19 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/04 13:58:54 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo*)data;
	while (!is_finish(&philo->n_eat, philo->kitchen)
	&& !is_one_died(philo->kitchen))
	{
		sem_wait(philo->kitchen->sem_forks);
		print_message(philo, TEXT_FORK);
		sem_wait(philo->kitchen->sem_wait);
		sem_wait(philo->kitchen->sem_forks);
		sem_post(philo->kitchen->sem_wait);
		print_message(philo, TEXT_FORK);
		print_message(philo, TEXT_EAT);
		gettimeofday(&philo->last_eat, NULL);
		my_usleep(philo->kitchen->t_to_eat, &philo->t_wake_up);
		sem_post(philo->kitchen->sem_forks);
		sem_post(philo->kitchen->sem_forks);
		(philo->n_eat)++;
		if (is_finish(&philo->n_eat, philo->kitchen))
			return (0);
		print_message(philo, TEXT_SLEEP);
		my_usleep(philo->kitchen->t_to_sleep, &philo->t_wake_up);
		print_message(philo, TEXT_THINK);
	}
	printf("fork\n");
	return (0);
}

void	create_thread(int i, t_kitchen *kitchen, int inc)
{
	t_philo		*philo;
	pid_t		pid;

	while (i < kitchen->n_philo)
	{
		philo = init_philosoph(kitchen, i + 1);
		ft_lstadd_back(&kitchen->philos, ft_lstnew(philo));
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Error : failed forw\n", 2);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			philosopher(philo);
			exit (0);
		}
		else
			philo->pid = pid;
		i += inc;
	}
}

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

int		ckeck_execute(int argc, char const *argv[], t_kitchen *kitchen)
{
	sem_unlink("fork");
	sem_unlink("wait");
	sem_close(kitchen->sem_print);
	sem_unlink("print");
	sem_unlink("die");
	if (argc < 5)
	{
		ft_putstr_fd("Error: not enought argument (min 4)\n", 2);
		return (1);
	}
	else if (argc > 6)
	{
		ft_putstr_fd("Error: too much arguments (max 5)\n", 2);
		return (1);
	}
	if (init_kitchen(kitchen, argc, argv))
	{
		ft_putstr_fd("Error: Allocation problem\n", 2);
		return (2);
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			status;
	int			i;

	if (ckeck_execute(argc, argv, &kitchen))
		return (1);
	kitchen.sem_forks = sem_open("fork", O_CREAT, S_IRWXU, (kitchen.n_philo));
	if (kitchen.sem_forks == SEM_FAILED)
	{
		ft_putstr_fd("Error : sem_open failed\n", 2);
		return (EXIT_FAILURE);
	}
	launch_group(2, &kitchen);
	while (-1 == check_all_die(&kitchen) && !kitchen.philo_finish)
		usleep(50);
	i = -1;
	if (kitchen.philo_die > 0)
	{
		t_list * cursor = kitchen.philos;
		t_philo * philo = NULL;
		while (cursor != 0)
		{
			philo = cursor->content;
			kill(philo->pid, SIGTERM);
			cursor = cursor->next;
		}
	}
	else
		waitpid(-1, &status, 0);
	free_kitchen(&kitchen);
	return 0;
}
