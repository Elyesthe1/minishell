#include "minishell.h"

static int	ft_sizelen(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_remp(int size, int n, char *str)
{
	str[size] = '\0';
	size--;
	while (n > 0 && size >= 0)
	{
		str[size] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		size;

	i = 0;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = ft_sizelen(n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		str[i] = '-';
		i++;
	}
	return (ft_remp(size, n, str));
}

