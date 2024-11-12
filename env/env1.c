/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:49 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:54:50 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stock_env(char **env_str, t_env **env)
{
	int	i;

	i = 0;
	while (env_str[i])
	{
		ft_lstadd_backenv(env, ft_lstnewenv(env_str[i]));
		i++;
	}
}

void	lst_freeenv(t_env **lexer)
{
	t_env	*tmp;

	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->str);
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
	char	*s;

	s = (char *) content;
	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strdup(s);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->name = get_env_name(s);
	new->value = get_env_value(s);
	new->next = NULL;
	return (new);
}
