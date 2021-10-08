/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:17:35 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:17:36 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  Allocates with malloc and returns a substring from the string ’s’. 
	The substring begins at index ’start’ and is of maximum size ’len’.
	Return the substring or NULL, if the allocation fails.           */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL || !s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		res[0] = '\0';
		return (res);
	}
	while (s[start] != '\0' && i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
