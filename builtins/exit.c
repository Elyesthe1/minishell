/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:47 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 15:26:55 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_msg(char **args, int outside_fork, int msg)
{
	char	*str;

	str = NULL;
	if (outside_fork)
		str = ft_strjoin_free(str, "exit\n");
	if (msg == 1)
	{
		str = ft_strjoin_free(str, "exit: ");
		str = ft_strjoin_free(str, args[1]);
		str = ft_strjoin_free(str, ": numeric argument required\n");
	}
	else if (msg == 2)
		str = ft_strjoin_free(str, "exit: too many arguments\n");
	if (!str)
		return ;
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
}

int	built_exit(char **args, int outside_fork)
{
	if (!args || (args && !args[1]))
	{
		perror_msg(args, outside_fork, 0);
		exit(g_status_code);
	}
	if (!ft_isint(args[1]))
	{
		perror_msg(args, outside_fork, 1);
		exit(2);
	}
	if (args_size(args) > 1)
	{
		perror_msg(args, outside_fork, 2);
		return (1);
	}
	perror_msg(args, outside_fork, 0);
	exit(ft_atoi(args[1]));
}
