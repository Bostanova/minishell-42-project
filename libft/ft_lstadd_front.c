#include "libft.h"

/*
	Adds the element ’new’ at the beginning of the list.

	**lst is the address of a pointer to the first link of a list.
	*new  is the address of a pointer to the element to be 
			added to the list.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
