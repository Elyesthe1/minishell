/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:53 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:54:54 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	if (i == 0)
		return (NULL);
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
	if (!str[i])
		return (ft_strdup(""));
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

t_env	*get_env_node(t_env **env, char *env_name, int n)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (ft_strcmp(env_node->name, env_name) == 0)
		{
			if (n == 0)
				ft_free(env_name);
			return (env_node);
		}
		env_node = env_node->next;
	}
	if (n == 0)
		free(env_name);
	return (NULL);
}

char	**get_env_path(t_env *env)
{
	t_env	*path_node;

	if (!env || !exists_in_env(&env, "PATH"))
		return (NULL);
	path_node = get_env_node(&env, "PATH", 1);
	if (!path_node)
		return (NULL);
	return (ft_split(path_node->value, ':'));
}
