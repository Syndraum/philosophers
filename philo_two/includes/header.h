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

# define TEXT_FORK "has taken a fork\n"
# define TEXT_EAT "is eating\n"
# define TEXT_SLEEP "is sleeping\n"
# define TEXT_THINK "is thinking\n"
# define TEXT_DIE "is died\n"

typedef struct		s_philo
{
	int				id;
	char			*s_id;
	// int				forks[2];
	void			*kitchen;
	struct timeval	last_eat;
	struct timeval	now;
}					t_philo;

typedef struct		s_kitchen
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_must_eat;
	sem_t			*sem;
	// pthread_mutex_t	*forks;
	pthread_t		*thread;
	t_philo			*philos;
	struct timeval	t_begin;
	char			philo_die;
}					t_kitchen;

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
void				ft_putstr_fd(char *s, int fd);
void				init_philosoph(t_philo *philo, t_kitchen *kitchen, int id);
int					init_kitchen(t_kitchen *kitchen, int ac, char const *av[]);
int					is_one_died(t_kitchen *kitchen);
int					is_die(t_philo *philo);
int					is_finish(int n, t_kitchen *kitchen);
long				diff_timestamp(struct timeval *begin, struct timeval *end);
char				*get_timestamp(struct timeval *begin, struct timeval *now);
void				print_message(t_philo *philo, char *text);
// int					eat_sleep(t_philo *philo);

#endif