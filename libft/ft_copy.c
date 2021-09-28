#include "./libft.h"

char	*ft_copy(char *str, int start)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	if (str && ((int)ft_strlen(str) > start))
	{
		res = (char *)ft_calloc((ft_strlen(str) - start + 1), sizeof(char));
		if (!res)
			return (NULL);
		while (str[start])
		{
			res[i] = str[start];
			i++;
			start++;
		}
		res[i] = '\0';
		free(str);
	}
	return (res);
}