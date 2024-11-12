#include "../minishell.h"

int	args_size(char **args)
{
	int	i;

	i = 1;
	while (args && args[i])
		++i;
	return (i - 1);
}

int	ft_split_len(char const *s, char c)
{
	size_t	i;
	int		count;
	int		is_delimiter;

	i = 0;
	count = 0;
	is_delimiter = 1;
	while (s[i])
	{
		if (is_delimiter && s[i] != c)
		{
			++count;
			is_delimiter = !is_delimiter;
		}
		else if (!is_delimiter && s[i] == c)
		{
			is_delimiter = !is_delimiter;
		}
		++i;
	}
	return (count);
}

static size_t	ft_strlen_delim(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	pos;

	strs = malloc(sizeof(char *) * (ft_split_len(s, c) + 1));
	i = 0;
	pos = 0;
	if (!strs)
		return (NULL);
	while (s[i])
	{
		if (ft_strlen_delim(&s[i], c) > 0)
		{
			strs[pos] = ft_calloc(ft_strlen_delim(&s[i], c) + 1, sizeof(char));
			if (!strs[pos])
				return (strs[pos] = NULL, ft_free_split(strs), NULL);
			ft_memcpy(strs[pos], &s[i], ft_strlen_delim(&s[i], c));
			i += ft_strlen_delim(&s[i], c);
			++pos;
		}
		else
			++i;
	}
	strs[pos] = NULL;
	return (strs);
}
