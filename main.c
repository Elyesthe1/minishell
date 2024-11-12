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
	set_signal_action();
	stock_env(env, &ev);
	prompt_start(&lexer, &ev);
	lst_freeenv(&ev);
	return (0);
}
