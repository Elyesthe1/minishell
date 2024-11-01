/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:24:55 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 16:51:05 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_freeenv(t_env **lexer)
{
	t_env *tmp;
	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->name);
		free((*lexer)->value);
		free((*lexer));
		(*lexer) = tmp;
	}
}

t_env	*ft_lstlastenv(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);

}

void	ft_lstadd_backenv(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlastenv(*lst);
	tmp->next = new;
}


t_env	*ft_lstnewenv(void *content)
{
	t_env	*new;
	char *s;

	s = (char*)content;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = get_env_name(s);
	new->value = get_env_value(s);
	new->str = s;
	new->next = NULL;
	return (new);
}

char	*get_env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		++i;
	}
	name[i] = '\0';
	return (name);
}

char	*get_env_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while(str[i] && str[i] != '=')
		++i;
	++i;
	value = malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
	if (!value)
		return (NULL);
	while (str[i + j])
	{
		value[j] = str[i + j];
		++j;
	}
	value[j] = '\0';
	return (value);
}

