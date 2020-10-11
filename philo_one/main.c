/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:37:48 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/11 18:43:12 by roalvare         ###   ########.fr       */
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

int	init_game(t_game *game, int argc, char const *argv[])
{
	game->n_must_eat = -1;
	game->n_philo = ft_atoi(argv[1]);
	game->t_to_die = ft_atoi(argv[2]);
	game->t_to_eat = ft_atoi(argv[3]);
	game->t_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		game->n_must_eat = ft_atoi(argv[5]);
	game->table.fourchette = malloc(sizeof(int) * game->n_philo);
	if (game->table.fourchette == 0)
		return (0);
	return (1);
}

void	free_game(t_game *game)
{
	free(game->table.fourchette);
}

int main(int argc, char const *argv[])
{
	t_game	game;

	if (argc < 5 )
	{
		ft_putstr_fd("Number of arguemnt to low (min 5)\n", 2);
		exit(1);
	}
	if (!init_game(&game, argc, argv))
	{
		ft_putstr_fd("Allocation problem\n", 2);
		exit(103);
	}
	free_game(&game);
}
