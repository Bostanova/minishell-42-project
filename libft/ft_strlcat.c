/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:16:54 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:16:55 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Конкатерирует содержимое нуль-терминированной строки                     */
/*   и буфера ограниченного размера.                                          */
/*   Возвращает размер строки, которую пыталась создать                       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	k = 0;
	while (src[k] != '\0')
		k++;
	return (i + k);
}
