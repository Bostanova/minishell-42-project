/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:16:12 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:16:16 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*res;
	char	*ptr_cast;
	size_t	i;

	i = 0;
	ptr_cast = (char *)ptr;
	res = (char *)malloc(size);
	if (res)
	{
		while (i < size && ptr_cast[i])
		{
			res[i] = ptr_cast[i];
			i++;
		}
		free(ptr);
		return ((void *)res);
	}
	free (ptr);
	return (NULL);
}
