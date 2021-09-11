/*
	копирование строки s2 в строку s1,
	начиная с байта с индeксом start 		*/

#include "libft.h"

void	ft_strscpy(char *s1, char *s2, int start)
{
	int	i;
	
	i = 0;
	while (s2[start])
	{
		s1[i] = s2[start];
		i += 1;
		start += 1;
	}
}
