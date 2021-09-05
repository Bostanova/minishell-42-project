#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Allocates enough space for count objects that are size bytes of memory   */
/*   each and return a pointers to the allocated memory.                      */
/*                                                                            */
/* ************************************************************************** */

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
