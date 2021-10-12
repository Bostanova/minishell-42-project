/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:14:25 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 19:14:26 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes and frees the given element and every successor 
**	of that element, using the function ’del’ and free(3).
**	The pointer to the list must be set to NULL
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*start;

	if (!lst || !del)
		return ;
	start = *lst;
	while (start)
	{
		tmp = start->next;
		del(start->content);
		free(start);
		start = tmp;
	}
	*lst = NULL;
}
