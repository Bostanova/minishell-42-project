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
