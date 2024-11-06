#include "../minishell.h"

char	*get_env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		++i;
	}
	name[i] = '\0';
	return (name);
}

char	*get_env_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		++i;
	++i;
	value = malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
	if (!value)
		return (NULL);
	while (str[i + j])
	{
		value[j] = str[i + j];
		++j;
	}
	value[j] = '\0';
	return (value);
}

bool	exists_in_env(t_env **env, char *env_name)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (ft_strcmp(env_node->name, env_name) == 0)
			return (true);
		env_node = env_node->next;
	}
	return (false);
}

t_env	*get_env_node(t_env **env, char *env_name)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (ft_strcmp(env_node->name, env_name) == 0)
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}
