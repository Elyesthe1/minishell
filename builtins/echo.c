#include "../minishell.h"

void	built_echo(char *str, bool newline)
{
	printf("%s", str);
	if (newline)
		printf("\n");
}
