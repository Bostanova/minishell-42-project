#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Find the first occurrence of c (converted to a unsigned char)            */
/*   in the string s.                                                         */
/*   Return a pointer to the byte located or NULL                             */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*s_cast;

	s_cast = (char *)s;
	i = 0;
	while (i < n)
	{
		if (s_cast[i] == c)
			return (s_cast + i);
		i++;
	}
	return (NULL);
}
