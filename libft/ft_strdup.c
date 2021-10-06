/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:13:07 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:13:08 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*   Allocates sufficient memory for a copy of the string s1, does the
     copy, and returns a pointer to it. The pointer may subsequently be 
	 used as an argument to the function free.
     If insufficient memory is available, NULL is returned              */

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res = ft_strcpy(res, s1);
	return (res);
}
