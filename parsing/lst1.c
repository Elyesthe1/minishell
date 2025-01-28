/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:52 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 13:47:58 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_free_parser(t_parser **parser)
{
	t_parser	*temp;

	while ((*parser) != NULL)
	{
		temp = (*parser)->next;
		free((*parser)->outfile.flag);
		free((*parser)->infile.flag);
		free_free((*parser)->infile.infile);
		free_free((*parser)->outfile.outfile);
		free_free((*parser)->str);
		free((*parser));
		(*parser) = temp;
	}
}

t_parser	*ft_lstlastcmd(t_parser *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	free_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
