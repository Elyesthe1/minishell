/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:41:40 by tovetouc          #+#    #+#             */
/*   Updated: 2024/11/01 17:06:03 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_lst_to_str(t_env **env)
{
	t_env	*env_node;
	char	*str;

	str = NULL;
	env_node = *env;
	while (env_node && env_node->next)
	{
		str = ft_strjoin(str, env_node->str, 0);
		if (!str)
			return (NULL);
		str = ft_strjoin(str, "\n", 0);
		if (!str)
			return (NULL);
		env_node = env_node->next;
	}
	if (!str)
		return (NULL);
	return (str);
}

void	built_env(t_env **env)
{
	char	*str;

	str = env_lst_to_str(env);
	printf("%s", str);
	free(str);
}
