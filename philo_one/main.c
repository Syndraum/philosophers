/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/12 22:32:01 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putstr_fd(char *s, int fd)
{
	int len;

	if (s != NULL)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}

void	init_philosoph(t_philo *philo, t_kitchen *kitchen, int id)
{
	philo->id = id;
	philo->forks[0] = id % kitchen->n_philo;
	philo->forks[1] = (id + 1) % kitchen->n_philo;
	philo->kitchen = kitchen;
	gettimeofday(&philo->last_eat, NULL);
}

int	init_kitchen(t_kitchen *kitchen, int argc, char const *argv[])
{
	int i;

	kitchen->philo_die = 0;
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
	i =-1;
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

void	free_kitchen(t_kitchen *kitchen)
{
	free(kitchen->forks);
	free(kitchen->philos);
	free(kitchen->thread);
}

int		is_one_died(t_kitchen *kitchen)
{
	return (kitchen->philo_die);
}

long	diff_timestamp(struct timeval *begin, struct timeval *end)
{
	long	diff;

	diff = end->tv_sec * 1000000 + end->tv_usec;
	diff -= begin->tv_sec * 1000000 + begin->tv_usec;
	return (diff);
}

char	*get_timestamp(struct timeval *begin, struct timeval *current)
{
	char	*ts;
	char	*tmp;
	long	diff;

	diff = diff_timestamp(begin, current) / 1000;
	tmp = ft_itoa(diff);
	ts = ft_strjoin(tmp, "ms ");
	free(tmp);
	if (ts == 0)
		return (0);
	return (ts);
}

void	print_message(t_philo *philo, char *text)
{
	char	*id;
	char	*ts;
	char	*str;
	char	*tmp;
	struct timeval	current;
	t_kitchen	*kitchen;

	kitchen = (t_kitchen*) philo->kitchen;
	gettimeofday(&current, NULL);
	ts = get_timestamp(&kitchen->t_begin, &current);
	tmp = ft_itoa(philo->id);
	id = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(ts, id);
	free(ts);
	free(id);
	str = ft_strjoin(tmp, text);
	free(tmp);
	ft_putstr_fd(str, 1);
	free(str);
}

void	eat_sleep(t_philo *philo)
{
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;

	if (is_one_died(kitchen))
		return ;
	print_message(philo, TEXT_EAT);
	usleep(kitchen->t_to_eat);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&kitchen->forks[philo->forks[0]]);
	pthread_mutex_unlock(&kitchen->forks[philo->forks[1]]);
	if (is_one_died(kitchen))
		return ;
	print_message(philo, TEXT_SLEEP);
	usleep(kitchen->t_to_sleep);
	if (is_one_died(kitchen))
		return ;
	print_message(philo, TEXT_THINK);
}

int		is_die(t_philo *philo)
{
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;
	struct timeval	current;
	long		diff;

	gettimeofday(&current, NULL);
	diff = diff_timestamp(&philo->last_eat, &current);
	if (diff >= kitchen->t_to_die)
	{
		kitchen->philo_die = 1;
		print_message(philo, TEXT_DIE);
		return (1);
	}
	return (0);
}

int		is_finish(int n, t_kitchen *kitchen)
{
	if (kitchen->n_must_eat != -1 && kitchen->n_must_eat == n)
		return (1);
	return (0);
}

void	*philosopher(void *data)
{
	int	n;

	t_philo		*philo = (t_philo*)data;
	t_kitchen	*kitchen = (t_kitchen*) philo->kitchen;
	gettimeofday(&philo->last_eat, NULL);
	n = 0;
	while (!is_finish(n, kitchen) && !is_one_died(kitchen) && !is_die(philo))
	{
		if (!pthread_mutex_lock(&kitchen->forks[philo->forks[0]]))
		{
			if (!pthread_mutex_lock(&kitchen->forks[philo->forks[1]]))
				eat_sleep(philo);
			else
				pthread_mutex_unlock(&kitchen->forks[philo->forks[0]]);
		}
		n++;
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
		init_philosoph(&kitchen.philos[i], &kitchen, i + 1);
		pthread_create(&kitchen.thread[i], NULL, philosopher, &kitchen.philos[i]);
	}
	i = -1;
	while (++i < kitchen.n_philo)
		pthread_join(kitchen.thread[i], NULL);
	// ft_putstr_fd("END\n", 1);
	free_kitchen(&kitchen);
	return (0);
}
