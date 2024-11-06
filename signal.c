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
 	return ;
}
