#include "minishell.h"

char *promt_config()
{
	char *user;
	char *session;
	char *cwd;
	char *s;
	int i;

	i = 0;
	user = getenv("USER");
	if (user == NULL)
		return ("minishell");
	session = getenv("SESSION_MANAGER");
	if (session == NULL)
		return ("minishell");
	while (*(session - 1) != '/')
		session++;	
	while (session[i] != '.')
		i++;
	session[i] = '\0';
	s = ft_strjoin(user, session, 2);
	cwd = getcwd(NULL, 0);
	s = ft_strjoin(s, cwd, 1);
	return (ft_strjoin(s, " ", 0));
}
void promt_start(t_lexer **lexer, t_env **env)
{
	char *line;
	int i = 0;
	char *promt;
	while (1)
	{
		promt = promt_config();
		line = readline(promt);
		add_history(line);
		lexer_config(lexer, line);
		lst_printf(*lexer);
		cmd_handler(line, env);
		free(promt);
		free(line);
		lst_free(lexer);
		if (i++ == 4)
			break;
	}
 }
