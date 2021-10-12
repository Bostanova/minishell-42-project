/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:14:15 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:14:16 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Adds the element ’new’ at the end of the list.

	**lst is the address of a pointer to the first link of a list.
	*new is the address of a pointer to the element to be
			added to the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = *lst;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = new;
		}
	}
}
