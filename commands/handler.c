/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:35 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 15:41:25 by tovetouc         ###   ########.fr       */
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

int	execute_outside_fork(char *cmd_name, char **args, int nb_of_pipes)
{
	if (nb_of_pipes > 0)
		return (false);
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

int	exec_outside_built(char **args, t_env **env)
{
	char	*cmd_name;

	cmd_name = args[0];
	if (ft_strcmp(cmd_name, "exit") == 0)
		g_status_code = built_exit(args, 1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		g_status_code = built_pwd(env);
	else if (ft_strcmp(cmd_name, "env") == 0)
		g_status_code = built_env(env);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		g_status_code = built_echo(args);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		g_status_code = built_unset(args, env);
	else if (ft_strcmp(cmd_name, "export") == 0)
		g_status_code = built_export(args, env);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		g_status_code = built_cd(args, env);
	return (0);
}

int	exec_built(char **args, t_env **env)
{
	char	*cmd_name;

	cmd_name = args[0];
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (built_exit(args, 0));
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (built_pwd(env));
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (built_env(env));
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (built_echo(args));
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (built_unset(args, env));
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (built_export(args, env));
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (built_cd(args, env));
	return (0);
}
