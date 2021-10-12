/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:14:02 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:14:03 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Allocates with malloc and returns a string representing the integer      */
/*   received as an argument. Negative numbers be handled                     */
/*                                                                            */
/* ************************************************************************** */

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

static char	*minnbr_hand(void)
{
	char	*res;

	res = (char *)malloc(12 * sizeof(char));
	if (!res)
		return (NULL);
	res = "-2147483648";
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = 0;
	if (n == -2147483648)
		return (minnbr_hand());
	len = ft_numlen(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	len -= 1;
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n >= 10)
	{
		res[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	res[len] = n + '0';
	return (res);
}
