/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:45 by erahal            #+#    #+#             */
/*   Updated: 2024/11/13 15:15:14 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_lst_to_str(t_env **env)
{
	t_env	*env_node;
	char	*str;

	str = NULL;
	env_node = *env;
	while (env_node)
	{
		str = ft_strjoin_free(str, env_node->str);
		if (!str)
			return (NULL);
		str = ft_strjoin_free(str, "\n");
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
	if (!str)
		return ;
	ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
}
