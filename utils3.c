#include "minishell.h"

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
		return (1);
	else
		return (0);
}

int	ft_isalnum(int n)
{
	if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122) || (n >= 48 && n <= 57))
		return (1);
	else
		return (0);
}

int	token_print_error(int i)
{
	if (i == 0)
		write(2, "bash: syntax error\n", 20);
	if (i == 1)
		write(2, "bash: syntax error near unexpected token \\`|\'", 46);
	return (1);
}

int	valid_dollar(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	exit_status(void)
{
	char	*itoa;
	int		i;

	itoa = ft_itoa(status_code);
	i = ft_strlen(itoa);
	free(itoa);
	return (i);
}
