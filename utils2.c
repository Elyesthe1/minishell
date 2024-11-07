
#include "minishell.h"


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
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	return (ft_strcpy_to_join(str, s1, s2));
}
