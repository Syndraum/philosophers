/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:58:50 by roalvare          #+#    #+#             */
/*   Updated: 2021/03/04 20:27:09 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>


# define TEXT_FORK " has taken a fork\n"
# define TEXT_EAT " is eating\n"
# define TEXT_SLEEP " is sleeping\n"
# define TEXT_THINK " is thinking\n"
# define TEXT_DIE " is died\n"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_kitchen
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_must_eat;
	sem_t			*sem_forks;
	pthread_t		*thread;
	t_list			*philos;
	struct timeval	t_begin;
	sem_t			*sem_die;
	char			philo_die;
	int				philo_finish;
	sem_t			*sem_print;
	sem_t			*sem_wait;
	int				remain;
}					t_kitchen;

typedef struct		s_philo
{
	int				id;
	char			*s_id;
	sem_t			*sem_last_eat;
	t_kitchen		*kitchen;
	struct timeval	last_eat;
	struct timeval	now;
	struct timeval	t_wake_up;
	pid_t			pid;
	int				n_eat;
	pthread_t		thread;
}					t_philo;

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
void				ft_putstr_fd(char *s, int fd);

t_philo				*init_philosoph(t_kitchen *kitchen, int id);
int					init_kitchen(t_kitchen *kitchen, int ac, char const *av[]);
int					is_one_died(t_kitchen *kitchen);
int					check_all_die(t_kitchen *kitchen);
int					check_die(t_philo * philo);
int					is_die(t_philo *philo);
int					is_died(t_kitchen *k, struct timeval *b, struct timeval *e);
void				my_usleep(int t_sleep, struct timeval *t_wake_up);
int					is_finish(int *n, t_kitchen *kitchen);
long				diff_timestamp(struct timeval *begin, struct timeval *end);
char				*get_timestamp(struct timeval *begin, struct timeval *now);
int					print_message(t_philo *philo, char *text);
void				free_kitchen(t_kitchen *kitchen);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));

#endif
