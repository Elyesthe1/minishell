/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:46:38 by tovetouc          #+#    #+#             */
/*   Updated: 2024/11/05 11:40:52 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// MAYBE ESCAPE " IN STR FOR IT TO BE LIKE BASH
char	*env_to_export_fmt(t_env **env)
{
	t_env	*env_node;
	char	*export_str;
	char	*str;

	env_node = *env;
	export_str = NULL;
	while (env_node && env_node->next)
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
			return (free(str),  NULL);
		free(str);
		env_node = env_node->next;
	}
	if (!export_str)
		return (NULL);
	return (export_str);
}

void built_export(t_env **env)
{
	char	*str;

	str = env_to_export_fmt(env);
	printf("%s", str);
	free(str);
}
