#include "minishell.h"

char	*var_replace(char **line, t_env **env)
{
	int		quote[2];
	char	*s;
	int		index[2];

	index[0] = 0;
	index[1] = 0;
	quote[0] = 0;
	quote[1] = 0;
	s = malloc(sizeof(char) * (bigline(ft_strdup((*line)), env) + 1));
	while ((*line)[index[0]])
	{
		if ((*line)[index[0]] == '\'' && quote[1] == 0)
			var_replace1(quote, 0);
		if ((*line)[index[0]] == '\"' && quote[0] == 0)
			var_replace1(quote, 1);
		if ((*line)[index[0]] == '$' && (in_quote(quote) == 2
				|| in_quote(quote) == 0))
			remp(&s, index, *line, env);
		else
			var_replace2(index, &s, line);
	}
	s[index[1]] = '\0';
	free(*line);
	return (s);
}

char	*prompt_config(void)
{
	char	*user;
	char	*session;
	char	*cwd;
	char	*s;
	int		i;

	i = 0;
	user = getenv("USER");
	if (user == NULL || !user)
		return (ft_strdup("minishell"));
	session = getenv("SESSION_MANAGER");
	if (session == NULL || !session)
		return (ft_strdup("minishell"));
	while (*session && *(session - 1) != '/')
		session++;
	while (*session && session[i] != '.')
		i++;
	session[i] = '\0';
	s = ft_strjoin_prompt(user, session, 2);
	cwd = getcwd(NULL, 0);
	s = ft_strjoin_prompt(s, cwd, 1);
	return (ft_strjoin_prompt(s, " ", 0));
}

void	prompt_start(t_lexer **lexer, t_env **env)
{
	char		*line;
	char		*prompt;
	t_parser	*parser;

	parser = NULL;
	while (1)
	{
		prompt = prompt_config();
		line = readline(prompt);
		if (line == NULL)
			ctrl_d(prompt, line);
		add_history(line);
		line = var_replace(&line, env);
		lexer_config(lexer, line, &parser);
		lst_printf(*lexer, parser);
		free_all(prompt, line, lexer, &parser);
	}
	rl_clear_history();
}
