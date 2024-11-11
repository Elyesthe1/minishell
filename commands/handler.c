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

void	execute_builtin(char *cmd_name, char **args, t_env **env)
{
	printf("executing builtin - %s\n", cmd_name);
	if (ft_strcmp(cmd_name, "exit") == 0)
		built_exit(0);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		built_pwd();
	else if (ft_strcmp(cmd_name, "env") == 0)
		built_env(env);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		built_echo("echo", args);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		built_unset("USER", env);
	else if (ft_strcmp(cmd_name, "export") == 0)
		built_export(env);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		built_cd(env, "-");
}

// void	cmd_handler(char *cmd_name, t_env **env)
// {
// 	if (!is_builtin(cmd_name))
// 	{
// 		printf("not implemented yet\n");
// 		return ;
// 	}
// 	execute_builtin(cmd_name, env, env);
// }
