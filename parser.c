#include "minishell.h"

int	how_much_cmd(t_lexer *lexer, t_parser **parser)
{
	int		i;
	int		infile;
	int		outfile;
	t_lexer	*temp;

	i = 0;
	temp = lexer;
	outfile = 0;
	infile = 0;
	while (lexer && lexer->token.token != 5)
	{
		while (lexer && lexer->token.token == 0)
			how_much_cmd1(&lexer, &i, 0);
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
			how_much_cmd1(&lexer, &outfile, 1);
		else if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
			how_much_cmd1(&lexer, &infile, 1);
	}
	alloc(parser, infile, outfile, temp);
	return (i);
}

t_parser	*ft_lstnewcmd(t_lexer *lexer)
{
	t_parser	*new;
	t_lexer		*temp;
	int			i[2];

	i[0] = 0;
	temp = lexer;
	new = (t_parser *)malloc(sizeof(t_parser));
	i[1] = how_much_cmd(lexer, &new) + 1;
	new->str = malloc(sizeof(char *) * i[1]);
	while (i[0] < i[1] - 1)
	{
		if (lexer->token.token == 0)
		{
			new->str[i[0]] = malloc(sizeof(char) * ft_strlen(lexer->str) + 1);
			i[0]++;
		}
		if (i[0] < i[1] - 1 && lexer->token.token != 0
			&& lexer->token.token != 5)
			lexer = lexer->next->next;
		else
			lexer = lexer->next;
	}
	new->str[i[0]] = 0;
	fill(&new, temp, i[1]);
	return (new);
}

void	parser_config(t_lexer **lexer, t_parser **parser)
{
	t_lexer	*temp;

	if (!(*lexer))
		return ;
	if ((*lexer)->token.token == 5 && token_print_error(1))
		return ;
	temp = (*lexer);
	ft_lstadd_backcmd(parser, ft_lstnewcmd(*lexer));
	while ((*lexer))
	{
		if ((*lexer) && (*lexer)->token.token == 5)
		{
			(*lexer) = (*lexer)->next;
			ft_lstadd_backcmd(parser, ft_lstnewcmd(*lexer));
		}
		(*lexer) = (*lexer)->next;
	}
	(*lexer) = temp;
}

void	its_a_word(t_lexer **lexer, char *l, int *j, int q[2])
{
	int	i;

	i = 0;
	while (l[i] && ((is_ws(l[i]) == 0 && is_token(l[i]) == 0) || in_quote(q)))
	{
		if (l[i] == '\'' && q[1] == 0)
		{
			if (q[0] == 1)
				q[0] = 0;
			else if (q[0] == 0)
				q[0] = 1;
		}
		if (l[i] == '\"' && q[0] == 0)
		{
			if (q[1] == 1)
				q[1] = 0;
			else if (q[1] == 0)
				q[1] = 1;
		}
		i++;
	}
	l[i] = '\0';
	ft_lstadd_back(lexer, ft_lstnew(l));
	*j += i;
	free(l);
}

int	lexer_config(t_lexer **lexer, char *line, t_parser **parser)
{
	int	i;
	int	quote[2];
	int	token;

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	if (quote_checker(line) == 1)
		return (-1);
	while (line && line[i])
	{
		if (is_token(line[i]) && in_quote(quote) == 0)
		{
			if (is_valid_token(line + i) < 0 && token_print_error(0))
				return (-1);
			token = ft_lstadd_back(lexer, ft_lstnewt(is_valid_token(line + i)));
			greed_line(token, &i);
		}
		if (is_ws(line[i]) == 0 && (is_token(line[i]) == 0 || in_quote(quote)))
			its_a_word(lexer, ft_strdup(&line[i]), &i, quote);
		while (line[i] && is_ws(line[i]))
			i++;
	}
	parser_config(lexer, parser);
	return (1);
}
