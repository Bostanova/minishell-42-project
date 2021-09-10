#include "libft.h"

/*   Allocates sufficient memory for a copy of the string s1, does the
     copy, and returns a pointer to it. The pointer may subsequently be 
	 used as an argument to the function free.
     If insufficient memory is available, NULL is returned              */

char	*ft_strdup(const char *s1)
{
	char	*res;
	
	res = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res = ft_strcpy(res, s1);
	return (res);
}
