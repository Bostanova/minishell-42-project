#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (-1);
	}	
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (0);
}
