#include "libft.h"

/*
**	Adds the element ’new’ after position 'pos'.
**
**	**lst is the address of a pointer to the first link of a list.
**	*new is the address of a pointer to the element to be
**			added to the list.
*/

void	ft_lstadd_pos(t_list **lst, t_list *new, int pos)
{
	t_list	*tmp;
	int		i;

	if (pos >= ft_lstsize(*lst))
	{
		ft_putstr("Error: position bigger than length of list");
		exit(1);
	}
	i = 0;
	tmp = *lst;
	while (i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	tmp->next = new;
}
