/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:36 by erahal            #+#    #+#             */
/*   Updated: 2024/11/15 13:38:40 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status_code;

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

void bigline1(int i[2], char *av, char c)
{
	if (c == '0')
	{
		i[0] += ft_strlen(av);
		i[1]++;
	}
	else
		i[1]++;
}

int	bigline(char *l, t_env **env, char *av)
{
	int		i[2];
	t_env	*node;

	i[1] = 0;
	i[0] = ft_strlen(l);
	while (*l && l[i[1]])
	{
		if (l[i[1]] == '$')
		{
			i[1]++;
			node = get_env_node(env, var_name(ft_strdup(l + i[1])), 0);
			if (node)
				i[0] += ft_strlen(node->str);
			if (l[i[1]] == '?')
				i[0] += exit_status();
			if (ft_isdigit(l[i[1]]))
				bigline1(i, av, l[i[1]]);
			else
				while (l[i[1]] && (ft_isalnum(l[i[1]]) || l[i[1]] == '_'))
					i[1]++;
		}
		else if (l[i[1]])
			i[1]++;
	}
	return (i[0] + free_zero(l));
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
	if (line[index[0]] == '?')
	{
		last_status(s, index);
		return ;
	}
	while (line[index[0]] && (ft_isalnum(line[index[0]])
			|| line[index[0]] == '_'))
		index[0]++;
}

void	var_replace2(int index[2], char **s, char **line, int *heredoc)
{
	(*s)[index[1]] = (*line)[index[0]];
	index[0]++;
	index[1]++;
	if (*heredoc)
	{
		while ((*line)[index[0]] && (*line)[index[0]] != '$')
		{
			(*s)[index[1]] = (*line)[index[0]];
			index[0]++;
			index[1]++;
		}
		while ((*line)[index[0]] && !is_ws((*line)[index[0]]))
		{
			(*s)[index[1]] = (*line)[index[0]];
			index[0]++;
			index[1]++;
		}
		*heredoc = 0;
	}
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
