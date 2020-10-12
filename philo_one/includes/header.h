#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define TEXT_FORK "has taken a fork\n"
# define TEXT_EAT "is eating\n"
# define TEXT_SLEEP "is sleeping\n"
# define TEXT_THINK "is thinking\n"
# define TEXT_DIE "is died\n"

typedef struct s_philo
{
	int			id;
	void		*kitchen;
	struct timeval	last_eat;
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

size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
void			ft_putstr_fd(char *s, int fd);

#endif