/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:45 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 13:45:40 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_lstnewt(int content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->token.token = content;
	new->next = NULL;
	return (new);
}

int	lst_free(t_lexer **lexer)
{
	t_lexer	*tmp;

	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->str);
		free((*lexer));
		(*lexer) = tmp;
	}
	return (1);
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

int	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer		*tmp;

	if (!new)
		return (-1);
	if (*lst == NULL)
	{
		(*lst) = new;
		return ((*lst)->token.token);
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	return (new->token.token);
}

t_lexer	*ft_lstnew(void *content)
{
	t_lexer	*new;
	char	*s;

	s = (char *)content;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->str = malloc(sizeof(char) * (ft_strlen_quote_parse(s) + 1));
	if (!new)
		return (NULL);
	text_parse_quote(&new, s);
	new->token.token = 0;
	new->next = NULL;
	return (new);
}
