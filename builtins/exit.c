#include "../minishell.h"

int	built_exit(char **args)
{
	int	i;

	i = 1;
	if (!args || (args && !args[1]))
		return (0);
	if (!ft_isint(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
	if (args_size(args) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	return (ft_atoi(args[1]));
}
