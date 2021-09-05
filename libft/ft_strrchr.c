#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Find the last occurrence of c (converted to a char)                      */
/*   in the string pointed to by s.                                           */
/*   Return a pointer to the located character or NULL                        */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i--;
	}
	if (!c && s[i] == '\0')
		return ((char *)s + i);
	return (0);
}
