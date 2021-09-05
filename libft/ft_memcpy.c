#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Copy n byte from src to dst. If overlap, behavior is undefined           */
/*   Return pointer to dst                                                    */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_tmp;
	const unsigned char	*src_tmp;

	dst_tmp = dst;
	src_tmp = src;
	i = 0;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	dst = (void *)dst_tmp;
	return (dst);
}
