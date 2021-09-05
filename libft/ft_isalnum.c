#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   the input parameter is the value of the character in the ascii table     */
/*   (their numeric values), for example:                                     */
/*   instead character B you have to write 'B' or 66                          */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
