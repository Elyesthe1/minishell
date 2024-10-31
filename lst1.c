/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:24:55 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 14:58:44 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_freeenv(t_env **lexer)
{
	t_env *tmp;
	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->var_env);
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
	int i;

	i = 0;
	s = (char*)content;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	while (s[i] != '=')
		i++;
	new->var_env = malloc(sizeof(char) * (i +1 ));
	i = 0;
	while (s[i] != '=')
	{
		new->var_env[i] = s[i];
		i++;
	}
	new->var_env[i] = '\0';
	new->str = s;
	new->next = NULL;
	return (new);
}
