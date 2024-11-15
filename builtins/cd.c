/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:42 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 16:49:42 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_directory_path(t_env **env, char *directory_path)
{
	if (!directory_path)
	{
		if (!exists_in_env(env, "HOME"))
		{
			write(STDERR_FILENO, "cd: HOME not set\n", ft_strlen("cd: HOME not set\n"));
			return (NULL);
		}
		directory_path = get_env_node(env, "HOME", 1)->value;
	}
	else if (ft_strcmp(directory_path, "-") == 0)
	{
		if (!exists_in_env(env, "OLDPWD"))
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", ft_strlen("cd: OLDPWD not set\n"));
			return (NULL);
		}
		directory_path = get_env_node(env, "OLDPWD", 1)->value;
		printf("%s\n", directory_path);
	}
	return (directory_path);
}

void	execute_error(char *directory_path, char *strerr)
{
	char	*str;

	str = NULL;
	str = ft_strjoin_free(str, "cd: ");
	str = ft_strjoin_free(str, directory_path);
	str = ft_strjoin_free(str, ": ");
	str = ft_strjoin_free(str, strerr);
	str = ft_strjoin_free(str, "\n");
	if (!str)
		return;
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
}

int	execute_cd(char *directory_path, t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	directory_path = get_directory_path(env, directory_path);
	if (!directory_path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = ft_strdup(getenv("PWD"));
	// printf("old_pwd: %s\n", old_pwd);
	if (chdir(directory_path) != 0)
	{
		execute_error(directory_path, strerror(errno));
		return (free(old_pwd), 1);
	}
	pwd = getcwd(NULL, 0);
	if (!exists_in_env(env, "OLDPWD"))
		add_to_env(env, "OLDPWD", old_pwd);
	else
		change_env_value(env, "OLDPWD", old_pwd);
	if (!exists_in_env(env, "PWD"))
		add_to_env(env, "PWD", pwd);
	else
		change_env_value(env, "PWD", pwd);
	return (free(old_pwd), free(pwd), 0);
}

int	built_cd(char **args, t_env **env)
{
	if (args_size(args) > 1)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", ft_strlen("cd: too many arguments\n"));
		return (1);
	}
	return (execute_cd(args[1], env));
}
