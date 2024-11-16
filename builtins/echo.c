/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:43 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 15:27:07 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_arg(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] && (str[i] != '-' || (str[i] == '-' && !str[i + 1])))
		return (0);
	++i;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

int	built_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args && args[i] && is_n_arg(args[i]))
	{
		newline = 0;
		++i;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
