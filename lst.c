/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:58:31 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 10:47:41 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_free(t_lexer **lexer)
{
	t_lexer *tmp;
	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer));
		(*lexer) = tmp;
	}
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}


void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;
	static int index = 1;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	new->prev = tmp;
	tmp->next = new;
	tmp->i = index++;
}


t_lexer	*ft_lstnew(void *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

