/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:35 by erahal            #+#    #+#             */
/*   Updated: 2024/11/13 16:53:22 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	return (false);
}

int	execute_outside_fork(char *cmd_name, char **args)
{
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd_name, "export") == 0)
	{
		if (args[1] == NULL)
			return (false);
		return (true);
	}
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	return (false);
}

int	exec_built(char **args, t_env **env)
{
	char	*cmd_name;

	cmd_name = args[0];
	if (ft_strcmp(cmd_name, "exit") == 0)
		built_exit(args);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		built_pwd(env);
	else if (ft_strcmp(cmd_name, "env") == 0)
		built_env(env);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		built_echo(args);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		built_unset(args, env);
	else if (ft_strcmp(cmd_name, "export") == 0)
		built_export(args, env);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		built_cd(args, env);
	return (0);
}
