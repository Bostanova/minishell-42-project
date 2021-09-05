#include "libft.h"

/* Locates the first occurrence of the null-terminated string needle in the 
   null-terminated string haystack. If needle is an empty string,           
   haystack is returned; if needle occurs nowhere in haystack, NULL is      
   returned; otherwise a pointer to the first character of the first        
   occurrence of needle is returned */

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*s1;
	char	*s2;
	char	*res;
	int		cmp;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	if (s2[0] == '\0')
		return (s1);
	res = ft_strchr(s1, s2[0]);
	if (res)
	{
		cmp = ft_strncmp(res, s2, (ft_strlen(s2)));
		if (cmp == 0)
			return (res);
	}
	return (NULL);
}
