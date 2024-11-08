#include "minishell.h"

void	ctrl_d(char *prompt, char *line)
{
	free(prompt);
	free(line);
	rl_clear_history();
	printf("exit\n");
	exit(0);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal_action(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
