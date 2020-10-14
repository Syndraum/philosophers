/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:54:26 by mazoise           #+#    #+#             */
/*   Updated: 2020/10/14 14:45:03 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_first_c(char *number, int n)
{
	*number = (n == 0) ? '0' : 0;
	*number = (n < 0) ? '-' : *number;
}

char		*ft_itoa(int n)
{
	char	*number;
	int		len;
	int		tmp;
	int		i;

	number = NULL;
	len = (n <= 0) ? 1 : 0;
	tmp = n;
	i = 0;
	while (tmp != 0)
	{
		len++;
		tmp /= 10;
	}
	tmp = n;
	if (!(number = ft_calloc(len + 1, sizeof(char))))
		return (number);
	ft_first_c(number, n);
	while (tmp != 0)
	{
		number[len - 1 - i] = ft_abs(tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	return (number);
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
