#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			id;
	int			last_eat;
	void		*kitchen;
}				t_philo;

typedef struct	s_kitchen
{
	int			n_philo;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			n_must_eat;
	pthread_mutex_t	*forks;
	pthread_t	*thread;
	t_philo		*philos;
}				t_kitchen;

#endif