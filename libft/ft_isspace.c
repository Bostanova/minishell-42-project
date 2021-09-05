#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   check the input parameter is one of folowing standart characters:        */
/*   '\t'   '\n'    '\v'    '\f'    '\r'    ' '                               */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
