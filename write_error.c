

#include "minishell.h"

int	token_print_error(void)
{
	write(2, "bash: syntax error near unexpected token\n", 42);
	return (1);
}
