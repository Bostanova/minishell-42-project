#include "libft.h"

static int	words(char const *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	wordlen(char const *s)
{
	int	len;

	len = 0;
	while (!ft_isspace(s[len]) && s[len] != '\0')
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

static char	**copy(char const *s, int words, char **res)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		while (ft_isspace(*s))
			s++;
		len = wordlen(s);
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

char	**ft_split_with_spaces(char const *s)
{
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	i = words(s);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	res = copy(s, i, res);
	return (res);
}
