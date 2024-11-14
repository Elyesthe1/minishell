/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:51 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 16:55:56 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cwd()
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	get_pwd_env(t_env **env)
{
	t_env	*env_node;
	
	if (!env)
		return (-1);
	env_node = get_env_node(env, "PWD", 1);
	if (!env_node)
		env_node = get_env_node(env, "OLDPWD", 1);
	if (!env_node)
		return (-1);
	printf("%s\n", env_node->value);
	return (0);
}

int get_env_pwd()
{
	char	*env_pwd;

	env_pwd = getenv("PWD");
	if (!env_pwd)
		return (-1);
	printf("%s\n", env_pwd);
	return (0);
}

int	built_pwd(t_env **env)
{
	(void)env;
	if (get_cwd() == 0)
		return (0);
	if (get_pwd_env(env) == 0)
		return (0);
	if (get_env_pwd() == 0)
		return (0);
	write(STDERR_FILENO, "pwd failed\n", 12);
	return (1);	
}
