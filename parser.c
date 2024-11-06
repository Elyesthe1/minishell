#include "minishell.h"


void parser_config(t_lexer **lexer, t_parser **parser)
{
	int i;

	i = 0;

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
		return (2);
	while (line && line[i])
	{
		if (is_token(line[i]) && in_quote(quote) == 0)
		{
			if (is_valid_token(line + i) < 0 && token_print_error())
				return (1);
			token = ft_lstadd_back(lexer, ft_lstnewt(is_valid_token(line + i)));
			greed_line(token, &i);
		}
		if (is_ws(line[i]) == 0 && (is_token(line[i]) == 0 || in_quote(quote)))
			its_a_word(lexer, ft_strdup(&line[i]), &i, quote);
		while (line[i] && is_ws(line[i]))
			i++;
	}
	parser_config(lexer, parser);
	return (0);
}
