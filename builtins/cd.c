#include "../minishell.h"

// maybe modify to return "exit code"
char	*get_directory_path(t_env **env, char *directory_path)
{
	if (!directory_path)
	{
		if (!exists_in_env(env, "HOME"))
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		directory_path = get_env_node(env, "HOME", 1)->value;
	}
	else if (ft_strcmp(directory_path, "-") == 0)
	{
		if (!exists_in_env(env, "OLDPWD"))
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		directory_path = get_env_node(env, "OLDPWD", 1)->value;
		printf("%s\n", directory_path);
	}
	return (directory_path);
}

void	execute_error(char *directory_path, char *strerr)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(directory_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerr, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	execute_cd(char *directory_path, t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	directory_path = get_directory_path(env, directory_path);
	if (!directory_path)
		return (1);
	old_pwd = getcwd(NULL, 0);
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
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (execute_cd(args[1], env));
}
