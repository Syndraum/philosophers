/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:45:27 by roalvare          #+#    #+#             */
/*   Updated: 2020/10/14 18:45:29 by roalvare         ###   ########.fr       */
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
