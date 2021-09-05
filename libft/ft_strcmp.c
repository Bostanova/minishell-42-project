#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Lexicographically compare the null-terminated strings s1 and s2.         */
/*   Return an integer greater than, equal to or less than 0, according       */
/*   as string s1 greater than, equal to or less than 0 string s2             */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
