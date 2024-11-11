#include "../minishell.h"

void	free_env_node(t_env *env_node)
{
	free(env_node->name);
	free(env_node->value);
	free(env_node->str);
	free(env_node);
}

// MODIFY LATER TO ACCEPT ENV NAME
void	remove_from_env(char *env_name, t_env **env)
{
	t_env	*prev_node;
	t_env	*env_node;

	prev_node = NULL;
	env_node = *env;
	while (env_node && env_node->next && ft_strcmp(env_node->name, env_name) != 0)
	{
		prev_node = env_node;
		env_node = env_node->next;
	}
	if (!prev_node)
	{
		*env = env_node->next;
		free_env_node(env_node);
		return ;
	}
	prev_node->next = env_node->next;
	free_env_node(env_node);
}

void	built_unset(char *env_name, t_env **env)
{
	if (!exists_in_env(env, env_name))
		return ;
	printf("in env\n");
	remove_from_env(NULL, env);
}
