#include "../minishell.h"

int	built_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args && args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		++i;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
