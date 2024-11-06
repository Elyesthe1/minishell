
#include "minishell.h"

int	ft_strlen_quote_parse1(char *s, int quote[2], int *i)
{
	if (s[*i] && s[*i] == '\'' && quote[0] == 0 && quote[1] == 0)
	{
		quote[0] = 1;
		*i += 1;
		return (1);
	}
	else if (s[*i] && s[*i] == '\'' && quote[0] == 1 && quote[1] == 0)
	{
		quote[0] = 0;
		*i += 1;
		return (1);
	}
	else if (s[*i] && s[*i] == '\"' && quote[0] == 0 && quote[1] == 0)
	{
		quote[1] = 1;
		*i += 1;
		return (1);
	}
	else if (s[*i] && s[*i] == '\"' && quote[0] == 0 && quote[1] == 1)
	{
		quote[1] = 0;
		*i += 1;
		return (1);
	}
	return (0);
}

int	ft_strlen_quote_parse(char *s)
{
	int	t;
	int	i;
	int	status;
	int	quote[2];

	i = 0;
	t = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (s[i])
	{
		status = 0;
		if (s[i] == '\'' || s[i] == '\"')
			status = ft_strlen_quote_parse1(s, quote, &i);
		if (status == 0)
		{
			i++;
			t++;
		}
	}
	return (t);
}

int	quote_checker1(char *line, int quote[2])
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (quote[0] == 1 && (in_quote(quote) == 0 || quote[1] == 0))
				quote[0] = 0;
			else if (quote[0] == 0 && (in_quote(quote) == 0
					|| quote[1] == 0))
				quote[0] = 1;
		}
		if (line[i] == '\"')
		{
			if (quote[1] == 1 && (in_quote(quote) == 0 || quote[0] == 0))
				quote[1] = 0;
			else if (quote[1] == 0 && (in_quote(quote) == 0 || quote[0] == 0))
				quote[1] = 1;
		}
		i++;
	}
	if (quote[0] == 1 || quote[1] == 1)
		return (1);
	return (0);
}

int	quote_checker(char *line)
{
	int	quote[2];
	int	i;

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	if (quote_checker1(line, quote) == 1)
	{
		write(2, "bash: unexpected while looking for matching quote\n", 51);
		return (1);
	}
	return (0);
}
