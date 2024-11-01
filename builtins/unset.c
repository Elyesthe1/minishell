/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:50:54 by tovetouc          #+#    #+#             */
/*   Updated: 2024/11/01 17:12:02 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exists_in_env(char *env_name, t_env **env)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node && env_node->next)
	{
		if (ft_strcmp(env_node->name, "USER") == 0) // MODIFY LATER TO ACCEPT ENV NAMEs
		 	return (true);
		env_node = env_node->next;
	}
	return (false);
}

void	remove_from_env(char *env_name, t_env **env)
{
	t_env	*prev_node;
	t_env	*env_node;

	prev_node = NULL;
	env_node = *env;
	while (env_node && env_node->next && ft_strcmp(env_node->name, "USER") != 0) // MODIFY LATER TO ACCEPT ENV NAME
	{
		prev_node = env_node;
		env_node = env_node->next;
	}
	if (!prev_node)
	{
		*env = env_node->next;
		free(env_node->name);
		free(env_node->value);
		free(env_node);
		return;
	}
	prev_node->next = env_node->next;
	free(env_node->name);
	free(env_node->value);
	free(env_node);
}

void	built_unset(char *env_name, t_env **env)
{
	if (env_name)
	{
		printf("not implemented yet\n");
		return;
	}
	if (!exists_in_env(env_name, env))
		return;

	printf("in env\n");
	remove_from_env(NULL, env);
}
