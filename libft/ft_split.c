#include "libft.h"

static int	words(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static void	*memfree(char **res, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	**copy(char const *s, int words, char c, char **res)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = wordlen(s, c);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(res[i]))
			return (memfree(res, i));
		j = 0;
		while (j < len)
			res[i][j++] = *s++;
		res[i][j] = '\0';
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	i = words(s, c);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	res = copy(s, i, c, res);
	return (res);
}
