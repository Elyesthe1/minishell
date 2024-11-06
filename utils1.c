

#include "minishell.h"

int	in_quote(int *quote)
{
	if (quote[0] == 1 && quote[1] == 1)
		return (1);
	if (quote[0] == 0 && quote[1] == 1)
		return (1);
	if (quote[0] == 1 && quote[1] == 0)
		return (1);
	return (0);
}

int	text_parse_quote1(t_lexer **lexer, char **s, int *j, int quote[2])
{
	if ((*s)[quote[2]] == '\'' && quote[0] == 0 && quote[1] == 0)
	{
		quote[0] = 1;
		quote[2] += 1;
	}
	else if ((*s)[quote[2]] == '\'' && quote[0] == 1 && quote[1] == 0)
	{
		quote[0] = 0;
		(*lexer)->str[*j] = (*s)[quote[2]];
		quote[2] += 1;
	}
	else if ((*s)[quote[2]] == '\"' && quote[0] == 0 && quote[1] == 0)
	{
		quote[1] = 1;
		quote[2] += 1;
	}
	else if ((*s)[quote[2]] == '\"' && quote[0] == 0 && quote[1] == 1)
	{
		quote[1] = 0;
		(*lexer)->str[*j] = (*s)[quote[2]];
		quote[2] += 1;
	}
	else
		return (0);
	return (1);
}

void	text_parse_quote(t_lexer **lexer, char *s)
{
	int	j;
	int	status;
	int	quote[3];

	quote[2] = 0;
	j = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (s[quote[2]])
	{
		status = 0;
		status = text_parse_quote1(lexer, &s, &j, quote);
		if (status == 0)
		{
			(*lexer)->str[j] = s[quote[2]];
			quote[2]++;
			j++;
		}
	}
	(*lexer)->str[j] = '\0';
}

void	free_prompt(char *line, char *prompt, t_lexer **lexer)
{
	free(prompt);
	free(line);
	lst_free(lexer);
}

void	lst_printf(t_lexer *lexer)
{
	while (lexer)
	{
		printf("mot = %stoken = %d index == %d\n", lexer->str,
			lexer->token.token, lexer->i);
		lexer = lexer->next;
	}
}
