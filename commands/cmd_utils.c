/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:23 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:54:24 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*construct_command_path(char *path, char *command_name)
{
	size_t	i;
	size_t	j;
	char	*command_path;

	i = 0;
	j = 0;
	if (!path || !command_name)
		return (NULL);
	command_path = ft_calloc(ft_strlen(path) + ft_strlen(command_name) + 2,
			sizeof(char));
	if (!command_path)
		return (NULL);
	while (path[i])
	{
		command_path[i] = path[i];
		++i;
	}
	command_path[i++] = '/';
	while (command_name[j])
	{
		command_path[i + j] = command_name[j];
		++j;
	}
	return (command_path);
}

char	*get_command_path(char *command_name, t_env *env)
{
	char	**env_path;
	char	*command_path;
	size_t	i;

	if (ft_strlen(command_name) == 0)
		return (NULL);
	if (access(command_name, X_OK) == 0)
		return (ft_strdup(command_name));
	i = 0;
	env_path = get_env_path(env);
	command_path = NULL;
	if (!env_path)
		return (NULL);
	while (env_path[i])
	{
		command_path = construct_command_path(env_path[i], command_name);
		if (command_path && access(command_path, X_OK) == 0)
			break ;
		free(command_path);
		command_path = NULL;
		++i;
	}
	ft_free_split(env_path);
	return (command_path);
}

int	replace_command_name_by_path(char **str, t_env *env)
{
	char	*command_path;

	command_path = get_command_path(*str, env);
	if (!command_path)
	{
		ft_putstr_fd(*str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(1);
		return (-1);
	}
	free(*str);
	*str = command_path;
	return (0);
}
