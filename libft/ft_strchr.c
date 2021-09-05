#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Find the first occurrence of c (converted to a char)                     */
/*   in the string pointed to by s.                                           */
/*   Return a pointer to the located character or NULL                        */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (!c && s[i] == '\0')
		return ((char *)s + i);
	return (0);
}
