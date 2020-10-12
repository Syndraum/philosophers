/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazoise <mazoise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:03:51 by mazoise           #+#    #+#             */
/*   Updated: 2020/10/12 16:06:19 by mazoise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_bzero(void *s, size_t n)
{
	return (memset(s, 0, n));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = NULL;
	if (!(str = malloc(count * size)))
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}