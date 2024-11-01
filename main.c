/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:41:15 by erahal            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/01 17:19:27 by erahal           ###   ########.fr       */
=======
/*   Updated: 2024/11/01 17:10:59 by tovetouc         ###   ########.fr       */
>>>>>>> 95d67e54b9c070708fb8c6457eca95a729ed1dcf
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_lexer *lexer;
	t_env *ev;
	(void)av;
	if (ac != 1)
	{
		write(2, "no arguments are required\n", 27);
		exit(1);
	}
	lexer = NULL;
	ev = NULL;
	set_signal_action();
	stock_env(env, &ev);
	promt_start(&lexer, &ev);
	lst_freeenv(&ev);
	return (0);
}
