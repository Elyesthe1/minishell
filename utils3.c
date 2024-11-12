#include "minishell.h"

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
		return (1);
	else
		return (0);
}

int	ft_isalnum(int n)
{
	if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122) || (n >= 48 && n <= 57))
		return (1);
	else
		return (0);
}

int	token_print_error(int i)
{
	if (i == 0)
		write(2, "bash: syntax error\n", 20);
	if (i == 1)
		write(2, "bash: syntax error near unexpected token \\`|\'", 46);
	return (1);
}

int	valid_dollar(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	exit_status(void)
{
	char	*itoa;
	int		i;

	itoa = ft_itoa(g_status_code);
	i = ft_strlen(itoa);
	free(itoa);
	return (i);
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
