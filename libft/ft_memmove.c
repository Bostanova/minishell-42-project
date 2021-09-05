#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Copy n byte from string src to string dst. The two strongs may           */
/*   overlap. Return pointer to dst	                                          */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_cast;
	const unsigned char	*src_cast;

	dst_cast = (unsigned char *)dst;
	src_cast = (unsigned char *)src;
	i = 0;
	if (src < dst)
	{
		while (len--)
			dst_cast[len] = src_cast[len];
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	dst = (void *)dst_cast;
	return (dst);
}
