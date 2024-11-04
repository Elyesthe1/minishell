/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:20:30 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 17:15:37 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void stock_env(char **env_str, t_env **env)
{
	int i;

	i = 0;
	while (env_str[i])
	{
		ft_lstadd_backenv(env, ft_lstnewenv(env_str[i]));
		i++;
	}
}
