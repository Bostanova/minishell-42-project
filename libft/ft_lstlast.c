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
