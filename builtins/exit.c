/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:47 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 13:46:42 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_exit(char **args)
{
	if (!args || (args && !args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (!ft_isint(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (args_size(args) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(ft_atoi(args[1]));
}
