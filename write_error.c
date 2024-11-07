

#include "minishell.h"

int	token_print_error(void)
{
	write(2, "bash: syntax error\n", 20);
	return (1);
}
