#include "minishell.h"

char	*var_name(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		line[++i] = '\0';
		return (line);
	}
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	line[i] = '\0';
	return (line);
}

int bigline(char *line, t_env **env)
{
	int i;
	int j;
	t_env *node;

	j = 0;
	i = ft_strlen(line);
	while (line[j])
	{
		if (line[j] == '$')
		{
			node = get_env_node(env, var_name(ft_strdup(line + j +1)), 0);
			if (node)
				i += ft_strlen(node->str);
		}
		j++;
	}
	return (i);
}
void remp(char **s, int *j, int *i, char *line, t_env **env)
{
	t_env *node;
	int a;
	int p;

	a = 0;
	(*i) += 1;
	node = get_env_node(env,  var_name(ft_strdup(line + (*i))), 0);
	while ( node && node->value[a])
	{
		(*s)[*j] = node->value[a];
		a++;
		*j += 1;
	}
	if (ft_isdigit(line[(*i)]))
	{
		*i += 1;
		return;
	}
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i) += 1;
}
char 	*var_replace(char **line, t_env **env)
{
	int		quote[2];
	t_env	*node;
	char 	*s;
	int j;
	int		i;

	i = 0;
	j = 0;
	quote[0] = 0;
	quote[1] = 0;
	s = malloc(sizeof(char) * (bigline(ft_strdup((*line)), env) + 1));
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' && quote[1] == 0)
		{
			if (quote[0] == 1)
				quote[0] = 0;
			else if (quote[0] == 0)
				quote[0] = 1;
		}
		if ((*line)[i] == '\"' && quote[0] == 0)
		{
			if (quote[1] == 1)
				quote[1] = 0;
			else if (quote[1] == 0)
				quote[1] = 1;
		}
		if ((*line)[i] == '$' && ( in_quote(quote) == 2 || in_quote(quote) == 0))
			remp(&s, &j, &i, *line, env);
		else
		{
			s[j] = (*line)[i];
			i++;
			j++;
		}
	}
	s[j] = '\0';
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
		printf("%s\n", line);
		lexer_config(lexer, line, &parser);
		lst_printf(*lexer, parser);
		free_all(prompt, line, lexer, &parser);
	}
	rl_clear_history();
}
