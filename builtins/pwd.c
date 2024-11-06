#include "../minishell.h"

// TODO: CHANGE THIS LATER TO TAKE INTO ACCOUNT CD
void	built_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
