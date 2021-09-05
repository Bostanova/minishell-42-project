#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Copy n byte from src to dst before finding char c.If overlap,            */
/*   behavior is undefined. Return pointer to dst after char c                */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	cast_dst = (unsigned char *)dst;
	cast_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cast_dst[i] = cast_src[i];
		if (cast_src[i] == c)
		{
			dst = (void *)cast_dst;
			return (dst + i + 1);
		}
		i++;
	}
	return (0);
}
