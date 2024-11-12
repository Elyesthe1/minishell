#include "../minishell.h"

// protect malloc
char	**convert_env_to_envp(t_env *env)
{
	int		env_size;
	char	**envp;
	int		i;

	i = 0;
	env_size = get_env_size(env);
	envp = malloc(sizeof(char **) * (env_size + 1));
	while (env)
	{
		envp[i] = malloc(sizeof(char *) * (ft_strlen(env->str) + 1));
		ft_strcpy(envp[i], env->str);
		env = env->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}

int	get_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		++i;
	}
	return (i);
}
