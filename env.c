/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:20:30 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 14:31:32 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void stock_env(char **env, t_env **ev)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_backenv(ev, ft_lstnewenv(env[i]));
		i++;
	}
}
