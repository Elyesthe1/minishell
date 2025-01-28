/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:54 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:55:55 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill4(t_lexer **lexer, t_parser **parser, int i[3])
{
	while ((*lexer)->next->str[i[0]])
	{
		(*parser)->infile.infile[i[1]][i[0]] = (*lexer)->next->str[i[0]];
		i[0]++;
	}
	(*parser)->infile.infile[i[1]][i[0]] = '\0';
	if ((*lexer)->token.token == 1)
		(*parser)->infile.flag[i[1]] = 1;
	else
		(*parser)->infile.flag[i[1]] = 4;
	i[1]++;
	(*lexer) = (*lexer)->next->next;
}

void	fill3(t_lexer **lexer, t_parser **parser, int i[3])
{
	while ((*lexer)->next->str[i[0]])
	{
		(*parser)->outfile.outfile[i[2]][i[0]] = (*lexer)->next->str[i[0]];
		i[0]++;
	}
	(*parser)->outfile.outfile[i[2]][i[0]] = '\0';
	if ((*lexer)->token.token == 2)
		(*parser)->outfile.flag[i[2]] = 2;
	else
		(*parser)->outfile.flag[i[2]] = 3;
	i[2]++;
	(*lexer) = (*lexer)->next->next;
}

void	fill2(t_lexer *lexer, t_parser **parser)
{
	int	index[3];

	index[2] = 0;
	index[1] = 0;
	alloc1(lexer, parser);
	while (lexer && lexer->token.token != 5)
	{
		index[0] = 0;
		while (lexer && lexer->token.token == 0)
			lexer = lexer->next;
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
			fill3(&lexer, parser, index);
		else if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
			fill4(&lexer, parser, index);
	}
}

void	fill(t_parser **new, t_lexer *lexer, int size)
{
	int	i;
	int	j;

	i = 0;
	(*new)->next = NULL;
	if (lexer && lexer->str == NULL && !lexer->token.token)
		return ;
	while (i < size - 1)
	{
		j = 0;
		while (i < size - 1 && lexer->token.token != 0)
			lexer = lexer->next->next;
		while (lexer->str[j])
		{
			(*new)->str[i][j] = lexer->str[j];
			j++;
		}
		(*new)->str[i][j] = '\0';
		i++;
		lexer = lexer->next;
	}
}

void	ft_lstadd_backcmd(t_parser **lst, t_parser *new)
{
	t_parser	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlastcmd(*lst);
	tmp->next = new;
}
