#include "../minishell.h"

void	built_echo(char *str, char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (args && ft_strcmp(args[0], "-n"))
		newline = 0;
	while (args && args[i])
	{
		printf("echo");
	}
}
