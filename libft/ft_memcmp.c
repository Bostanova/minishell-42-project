#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Compares byte string s1 against byte string s2. Both strings zre assumed */
/*   to be n bytes long. Return 0, if strings are identical, otherwise        */
/*   return the difference between the first two difference byte              */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cast;
	unsigned char	*s2_cast;

	s1_cast = (unsigned char *)s1;
	s2_cast = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	i = 0;
	s1_cast = (unsigned char *)s1;
	s2_cast = (unsigned char *)s2;
	while (++i < n && *s1_cast == *s2_cast)
	{
		s1_cast++;
		s2_cast++;
	}
	return (*s1_cast - *s2_cast);
}
