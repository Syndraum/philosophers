#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_table
{
	int			*fourchette;
}				t_table;

typedef struct	s_game
{
	t_table		table;
	int			n_philo;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			n_must_eat;
}				t_game;


#endif