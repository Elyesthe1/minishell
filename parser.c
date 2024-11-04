/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:54:57 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 18:03:21 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void its_a_word(t_lexer **lexer, char *line, int *j, int qote[2])
{
	int i;

	i = 0;
	while (line[i] && it_is_white_space(line[i]) == 0 && (it_is_a_token(line[i]) == 0 || i_am_in_qote(qote)))
	{
		if (line[i] == '\'')
		{
			if (qote[0] == 1)
				qote[0] = 0;
			else if (qote[0] == 0)
				qote[0] = 1;
		}
		if (line[i] == '\"')
		{
			if (qote[1] == 1)
				qote[1] = 0;
			else if (qote[1] == 0)
				qote[1] = 1;
		}
		i++;
	}
	line[i] = '\0';
	ft_lstadd_back(lexer, ft_lstnew(line, i));
	*j += i;
	free(line);
}
int lexer_config(t_lexer **lexer, char *line)
{
	int i;
	int qote[2];
	int tocken;

	i = 0;
	qote[0] = 0;
	qote[1] = 0;
	if (quote_checker(line) == 1)
		return (2);
	while (line && line[i])
	{
		if (it_is_a_token(line[i]) && i_am_in_qote(qote) == 0)
		{
			if (it_is_valid_token(line + i) < 0 && token_print_error())
				return (1);
			tocken = ft_lstadd_back(lexer, ft_lstnewtoken(it_is_valid_token(line + i)));
			greed_line(tocken, &i);
		}
		if (it_is_white_space(line[i]) == 0 && (it_is_a_token(line[i]) == 0 || i_am_in_qote(qote)))
			its_a_word(lexer, ft_strdup(&line[i]), &i, qote);
	 	while (line[i] && it_is_white_space(line[i]))
			i++;
	}
	return (0);
}

