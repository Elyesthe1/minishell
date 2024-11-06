#include "../minishell.h"

// maybe modify to return "exit code"
char	*get_directory_path(t_env **env, char *directory_path)
{
	if (!directory_path)
	{
		if (!exists_in_env(env, "HOME"))
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		directory_path = get_env_node(env, "HOME")->value;
	}
	else if (ft_strcmp(directory_path, "-") == 0)
	{
		if (!exists_in_env(env, "OLDPWD"))
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
		directory_path = get_env_node(env, "OLDPWD")->value;
		printf("%s\n", directory_path);
	}
	return (directory_path);
}

void	built_cd(t_env **env, char *directory_path)
{
	char	*old_pwd;
	char	*pwd;

	directory_path = get_directory_path(env, directory_path);
	if (!directory_path)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (chdir(directory_path) != 0)
	{
		printf("cd: %s: %s\n", directory_path, strerror(errno));
		free(old_pwd);
		return ;
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
	free(old_pwd);
	free(pwd);
}
