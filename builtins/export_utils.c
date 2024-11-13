/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:48 by erahal            #+#    #+#             */
/*   Updated: 2024/11/13 15:15:04 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_identifier_error(char *str)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
}

void	manage_export(char **args, t_env **env)
{
	int		i;
	char	*env_name;
	char	*env_value;

	i = 1;
	while (args && args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			env_name = get_env_name(args[i]);
			env_value = get_env_value(args[i]);
			if (env_name)
				export_to_env(env, &env_name, &env_value);
			else
				export_identifier_error(args[i]);
		}
		++i;
	}
}

void	export_to_env(t_env **env, char **env_name, char **env_value)
{
	if (!exists_in_env(env, *env_name))
		add_to_env(env, *env_name, *env_value);
	else
		change_env_value(env, *env_name, *env_value);
	free(*env_name);
	free(*env_value);
}
