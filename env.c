#include "minishell.h"

void	stock_env(char **env, t_env **ev)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_backenv(ev, ft_lstnewenv(env[i]));
		i++;
	}
}
