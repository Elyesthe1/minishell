#include "minishell.h"

char	*var_name(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		line[++i] = '\0';
		return (line);
	}
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	line[i] = '\0';
	return (line);
}

int	bigline(char *line, t_env **env)
{
	int		i;
	int		j;
	t_env	*node;

	j = 0;
	i = ft_strlen(line);
	while (line[j])
	{
		if (line[j++] == '$')
		{
			node = get_env_node(env, var_name(ft_strdup(line + j)), 0);
			if (node)
				i += ft_strlen(node->str);
			if (ft_isdigit(line[j]))
				j++;
			else
				while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
					j++;
		}
		else
			j++;
	}
	free(line);
	return (i);
}

void	remp(char **s, int index[2], char *line, t_env **env)
{
	t_env	*node;
	int		a;

	a = 0;
	index[0]++;
	node = get_env_node(env, var_name(ft_strdup(line + index[0])), 0);
	while (node && node->value[a])
	{
		(*s)[index[1]] = node->value[a];
		a++;
		index[1]++;
	}
	if (ft_isdigit(line[index[0]]))
	{
		index[0]++;
		return ;
	}
	while (line[index[0]] && (ft_isalnum(line[index[0]])
			|| line[index[0]] == '_'))
		index[0]++;
}

void	var_replace2(int index[2], char **s, char **line)
{
	(*s)[index[1]] = (*line)[index[0]];
	index[0]++;
	index[1]++;
}

void	var_replace1(int quote[2], int i)
{
	if (i == 0)
	{
		if (quote[0] == 1)
			quote[0] = 0;
		else if (quote[0] == 0)
			quote[0] = 1;
	}
	else if (i == 1)
	{
		if (quote[1] == 1)
			quote[1] = 0;
		else if (quote[1] == 0)
			quote[1] = 1;
	}
}
