#include "../minishell.h"

// MAYBE ESCAPE " IN STR FOR IT TO BE LIKE BASH
char	*create_export_line(t_env *env_node)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen("declare -x ")
				+ ft_strlen(env_node->name)
				+ ft_strlen(env_node->value) + 5));
	if (!str)
		return (NULL);
	ft_strcpy(str, "declare -x ");
	ft_strcpy(&str[ft_strlen(str)], env_node->name);
	ft_strcpy(&str[ft_strlen(str)], "=\"");
	ft_strcpy(&str[ft_strlen(str)], env_node->value);
	ft_strcpy(&str[ft_strlen(str)], "\"\n");
	return (str);
}

char	*env_to_export_fmt(t_env **env)
{
	t_env	*env_node;
	char	*export_str;
	char	*str;

	env_node = *env;
	export_str = NULL;
	while (env_node)
	{
		str = malloc(sizeof(char) * (ft_strlen("declare -x ") + ft_strlen(env_node->name) + ft_strlen(env_node->value) + 5));
		if (!str)
			return (NULL);
		ft_strcpy(str, "declare -x ");
		ft_strcpy(&str[ft_strlen(str)], env_node->name);
		ft_strcpy(&str[ft_strlen(str)], "=\"");
		ft_strcpy(&str[ft_strlen(str)], env_node->value);
		ft_strcpy(&str[ft_strlen(str)], "\"\n");
		// printf("%s \n", str);
		export_str = ft_strjoin(export_str, str);
		if (!export_str)
			return (free(str), NULL);
		free(str);
		env_node = env_node->next;
	}
	if (!export_str)
		return (NULL);
	return (export_str);
}

void	add_to_env(t_env **env, char *env_name, char *env_value)
{
	char	*str;
	t_env	*env_node;

	str = malloc(sizeof(char) * (ft_strlen(env_name)
				+ ft_strlen(env_value) + 2));
	if (!str)
		return ;
	ft_strcpy(str, env_name);
	ft_strcpy(&str[ft_strlen(str)], "=");
	ft_strcpy(&str[ft_strlen(str)], env_value);
	env_node = ft_lstnewenv((void *) str);
	if (!env_node)
	{
		free(str);
		return ;
	}
	ft_lstadd_backenv(env, env_node);
	free(str);
}

void	change_env_value(t_env **env, char *env_name, char *env_value)
{
	char	*str;
	t_env	*env_node;

	env_node = *env;
	while (env_node && ft_strcmp(env_node->name, env_name) != 0)
		env_node = env_node->next;
	str = malloc(sizeof(char) * (ft_strlen(env_name)
				+ ft_strlen(env_value) + 2));
	if (!str)
		return ;
	ft_strcpy(str, env_name);
	ft_strcpy(&str[ft_strlen(str)], "=");
	ft_strcpy(&str[ft_strlen(str)], env_value);
	free(env_node->str);
	free(env_node->name);
	free(env_node->value);
	env_node->str = str;
	env_node->name = get_env_name(str);
	env_node->value = get_env_value(str);
}

// char	*str;
// str = env_to_export_fmt(env);
// printf("%s", str);
// free(str);
void	built_export(t_env **env)
{
	if (!exists_in_env(env, "TEST"))
	{
		printf("ADD_TO_ENV\n");
		add_to_env(env, "TEST", "TEST123");
	}
	else
	{
		printf("CHANGE_ENV_VALUE\n");
		change_env_value(env, "TEST", "XDCHANGED");
	}
}
