#include "minishell.h"

int	in_quote(int *quote)
{
	if (quote[0] == 1 && quote[1] == 1)
		return (1);
	if (quote[0] == 0 && quote[1] == 1)
		return (2);
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

void	free_all(char *line, char *prompt, t_lexer **lexer, t_parser **parser)
{
	free(prompt);
	free(line);
	lst_free(lexer);
	lst_free_parser(parser);
}

void	alloc1(t_lexer *lexer, t_parser **parser)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (lexer && lexer->token.token != 5)
	{
		while (lexer && lexer->token.token == 0)
			lexer = lexer->next;
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
		{
			(*parser)->outfile.outfile[i[0]] = malloc(sizeof(char)
					* (ft_strlen(lexer->next->str) + 1));
			lexer = lexer->next->next;
			i[0]++;
		}
		if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
		{
			(*parser)->infile.infile[i[1]] = malloc(sizeof(char)
					* (ft_strlen(lexer->next->str) + 1));
			lexer = lexer->next->next;
			i[1]++;
		}
	}
	(*parser)->outfile.outfile[i[0]] = 0;
	(*parser)->infile.infile[i[1]] = 0;
}

void	lst_printf(t_lexer *lexer, t_parser *parser)
{
	int	i;

	i = 0;
	while (lexer)
	{
		printf("mot = %s token = %d\n", lexer->str,
			lexer->token.token);
		lexer = lexer->next;
	}
	printf("\n");
	while (parser)
	{
		i = 0;
		while (parser && parser->str != NULL && parser->str && parser->str[i])
		{
			printf("%s\n", parser->str[i]);
			i++;
		}
		i = 0;
		while (parser && parser->infile.infile != NULL
			&& parser->infile.infile[i])
		{
			printf("infile == %s %d\n", parser->infile.infile[i], parser->infile.flag[i]);
			i++;
		}
		i = 0;
		while (parser && parser->outfile.outfile != NULL
			&& parser->outfile.outfile[i])
		{
			printf("outfile == %s %d\n", parser->outfile.outfile[i],
				parser->outfile.flag[i]);
			i++;
		}
		printf("NEXT\n");
		parser = parser->next;
	}
}
