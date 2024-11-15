/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:56 by erahal            #+#    #+#             */
/*   Updated: 2024/11/15 13:30:06 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

int	main(int ac, char **av, char **env)
{
	t_lexer	*lexer;
	t_env	*ev;

	(void)av;
	g_status_code = 0;
	if (ac != 1)
	{
		write(2, "no arguments are required\n", 27);
		exit(1);
	}
	lexer = NULL;
	ev = NULL;
	stock_env(env, &ev);
	set_signal_action();
	prompt_start(&lexer, &ev, av[0]);
	lst_freeenv(&ev);
	return (g_status_code);
}
