/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:28:53 by tovetouc          #+#    #+#             */
/*   Updated: 2024/11/16 14:42:12 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_strs_size(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		++i;
	return (i);
}

char	**sort_export_strs(char **strs, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (j < size)
		{
			if (ft_strcmp(strs[i], strs[j]) < 0)
			{
				tmp = ft_strdup(strs[i]);
				free(strs[i]);
				strs[i] = ft_strdup(strs[j]);
				free(strs[j]);
				strs[j] = tmp;
			}
			++j;
		}
		j = 0;
		++i;
	}
	return (NULL);
}

char	**env_to_export_strs(t_env *env)
{
	int		i;
	char	**strs;

	i = 0;
	strs = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!strs)
		return (NULL);
	while (env)
	{
		strs[i] = create_export_line(env);
		++i;
		env = env->next;
	}
	strs[i] = NULL;
	sort_export_strs(strs, export_strs_size(strs));
	return (strs);
}
