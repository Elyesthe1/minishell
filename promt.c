
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
	if (user == NULL || !user)
		return (ft_strdup("minishell"));
	session = getenv("SESSION_MANAGER");
	if (session == NULL || !session)
		return (ft_strdup("minishell"));
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
	char *promt;
	// t_parser *parser;
	while (1)
	{
		promt = promt_config();
		line = readline(promt);
		if (line == NULL)
			ctrl_D(promt, line);
		add_history(line);
		lexer_config(lexer, line);
		lst_printf(*lexer);
		free_promt(promt, line, lexer);
	}
	rl_clear_history();
 }
