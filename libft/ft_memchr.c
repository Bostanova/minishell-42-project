/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:15:06 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:15:07 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Find the first occurrence of c (converted to a unsigned char)            */
/*   in the string s.                                                         */
/*   Return a pointer to the byte located or NULL                             */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*s_cast;

	s_cast = (char *)s;
	i = 0;
	while (i < n)
	{
		if (s_cast[i] == c)
			return (s_cast + i);
		i++;
	}
	return (NULL);
}
