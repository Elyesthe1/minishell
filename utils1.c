

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
	}char *valueenv(char *s, t_env *env)
{
	
}
	(*lexer)->str[j] = '\0';
}

void	free_all(char *line, char *prompt, t_lexer **lexer, t_parser **parser)
{
	free(prompt);
	free(line);
	lst_free(lexer);
	lst_free_parser(parser);
}

void	lst_printf(t_lexer *lexer, t_parser *parser)
{
	int i = 0;
	while (lexer)
	{
		printf("mot = %s token = %d index == %d\n", lexer->str,
			lexer->token.token, lexer->i);
		lexer = lexer->next;
	}
	printf("\n");
	while (parser)
	{
		i = 0;
		while (parser && parser->str && parser->str[i])
		{
			printf("%s\n", parser->str[i]);
			i++;
		}
		i = 0;
		while ( parser->infile.infile != NULL && parser->infile.infile[i])
		{
			printf("infile == %s\n", parser->infile.infile[i]);
			i++;
		}
		i = 0;
		while ( parser->outfile.outfile != NULL && parser->outfile.outfile[i])
		{
			printf("outfile == %s %d\n", parser->outfile.outfile[i], parser->outfile.flag[i]);
			i++;
		}
		printf("NEXT\n");
		parser = parser->next;
	}
}
