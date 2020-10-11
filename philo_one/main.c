/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/12 00:28:49 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	ft_strlen(const char *str)
{
	size_t len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	int len;

	if (s != NULL)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}

int			ft_atoi(const char *str)
{
	int			signe;
	int			nbr;
	const char	*begin;

	signe = 1;
	nbr = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '-' || *str == '+')
		signe = (*(str++) == '-') ? -1 : 1;
	begin = str;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (str - begin == 18 && *str - '0' > 7)
		{
			if (signe == 1)
				return (-1);
			else if (signe == -1)
				return (0);
		}
		nbr = (nbr * 10) + (*str++ - '0');
	}
	return (nbr * signe);
}

void	init_philosoph(t_philo *philo, t_kitchen *kitchen, int id)
{
	philo->id = id;
	philo->kitchen = kitchen;
	philo->last_eat = 0; //need change
}

int	init_kitchen(t_kitchen *kitchen, int argc, char const *argv[])
{
	int i;

	kitchen->n_must_eat = -1;
	kitchen->n_philo = ft_atoi(argv[1]);
	kitchen->t_to_die = ft_atoi(argv[2]) * 1000;
	kitchen->t_to_eat = ft_atoi(argv[3]) * 1000;
	kitchen->t_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		kitchen->n_must_eat = ft_atoi(argv[5]);
	kitchen->forks = malloc(sizeof(pthread_mutex_t) * kitchen->n_philo);
	if (kitchen->forks == 0)
		return (0);
	i =-1;
	while (++i < kitchen->n_philo)
		pthread_mutex_init(&kitchen->forks[i], PTHREAD_MUTEX_INITIALIZER);
	kitchen->thread = malloc(sizeof(pthread_t) * kitchen->n_philo);
	if (kitchen->thread == 0)
		return (0);
	return (1);
}

void	free_kitchen(t_kitchen *kitchen)
{
	free(kitchen->forks);
	free(kitchen->thread);
}

void	eat_spleep(t_philo *philo, int first, int second)
{
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;

	usleep(kitchen->t_to_eat);
	philo->last_eat = 0; //Change
	pthread_mutex_unlock(&kitchen->forks[first]);
	pthread_mutex_unlock(&kitchen->forks[second]);
	usleep(kitchen->t_to_sleep);
}

void	*philosopher(void *data)
{
	int i;
	int sec;

	t_philo		*philo = (t_philo*) data;
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;
	i = -1;
	while (philo->last_eat + kitchen->t_to_die > timenow) //change
	{
		i = (i + 1) % kitchen->n_philo;
		if (!pthread_mutex_lock(&kitchen->forks[i]))
		{
			sec = (i + 1) % kitchen->n_philo;
			if (!pthread_mutex_lock(&kitchen->forks[sec]))
				eat_spleep(kitchen, i, sec);
			else
			{
				sec = (i - 1) % kitchen->n_philo;
				if (!pthread_mutex_lock(&kitchen->forks[sec]))
					eat_spleep(kitchen, i, sec);
			}
		}
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	t_kitchen	kitchen;
	int			i;

	if (argc < 5 )
	{
		ft_putstr_fd("Number of arguemnt to low (min 5)\n", 2);
		exit(1);
	}
	if (!init_kitchen(&kitchen, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		exit(2);
	}
	i=-1;
	while (++i < kitchen.n_philo)
	{
		pthread_create(kitchen.thread[0], NULL, philosopher, &kitchen.philos[i]);
	}
	i = -1;
	while (++i < kitchen.n_philo)
	{
		pthread_join(kitchen.thread[i], NULL);
	}
	
	free_kitchen(&kitchen);
}
