#include "minishell.h"

int	ft_atoi(const char *str)
{
	long long	number;
	int			sign;
	int			i;

	number = 0;
	sign = 1;
	i = 0;
	if (str[i] && str[i] == '-')
	{
		sign = -sign;
		++i;
	}
	while (str[i])
	{
		number = number * 10 + (str[i] - '0');
		++i;
	}
	number = number * sign;
	return (number);
}

int	ft_isint(char *str)
{
	long long	number;
	int			sign;
	int			i;

	number = 0;
	sign = 1;
	i = 0;
	if (str[i] && str[i + 1] && str[i] == '-')
	{
		sign = -sign;
		++i;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		number = number * 10 + (str[i] - '0');
		++i;
	}
	number = number * sign;
	if (number < INT_MIN || number > INT_MAX)
		return (0);
	return (1);
}
