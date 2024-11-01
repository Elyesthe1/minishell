/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:42:06 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 17:09:27 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler_quit(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0); // Remplacer la ligne actuelle
    rl_redisplay(); // Mettre à jour l'affichage
}

void set_signal_action(void)
{
 	t_signal act;

 	bzero(&act, sizeof(act));
 	act.sig_handler = &signal_handler_quit;
 	sigaction(SIGINT, &act, NULL);
}
