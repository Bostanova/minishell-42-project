/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:14:35 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:14:36 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 	This function takes as input a beginning of the list.
	Returns the last element of the list   */

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*res;
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		res = tmp;
		tmp = tmp->next;
	}
	return (res);
}
