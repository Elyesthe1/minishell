#include "minishell.h"

void	free_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	alloc(t_parser **parser, int infile, int outfile, t_lexer *lexer)
{
	(*parser)->infile.infile = malloc(sizeof(char *) * (infile + 1));
	(*parser)->outfile.outfile = malloc(sizeof(char *) * (outfile + 1));
	(*parser)->outfile.flag = malloc(sizeof(int) * outfile);
	(*parser)->infile.flag = malloc(sizeof(int) * infile);
	(*parser)->infile.fd = NULL;
	(*parser)->outfile.fd = NULL;
	fill2(lexer, parser);
}

void	how_much_cmd1(t_lexer **lexer, int *i, int n)
{
	if (n == 0)
	{
		*i += 1;
		(*lexer) = (*lexer)->next;
	}
	else
	{
		*i += 1;
		(*lexer) = (*lexer)->next->next;
	}
}

static char	*ft_strcpy_to_join(char *s1, char *s2, char *s3)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	while (s3[j])
	{
		s1[i] = s3[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	free(s2);
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	return (ft_strcpy_to_join(str, s1, s2));
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return ((char *) ft_calloc(1, sizeof(char)));
	i = 0;
	j = 0;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		++j;
	}
	free(s1);
	s1 = NULL;
	return (str);
}
