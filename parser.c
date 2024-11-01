/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:54:57 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 16:25:28 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void its_a_word(t_lexer **lexer, char *line, int *j)
{
	int i;

	i = 0;
	while (line[i] && it_is_white_space(line[i]) == 0 && it_is_a_token(line[i]) == 0)
		i++;
	line[i] = '\0';
	ft_lstadd_back(lexer, ft_lstnew(line, i));
	*j += i;
	free(line);
}
int lexer_config(t_lexer **lexer, char *line)
{
	int i;
	int tocken;

	i = 0;
	while (line[i])
	{
		if (it_is_a_token(line[i]))
		{
			if (it_is_valid_token(line + i) < 0)
			{
				write(2,"bash: syntax error near unexpected token\n", 42);
				return (1);
			}
			tocken = ft_lstadd_back(lexer, ft_lstnewtoken(it_is_valid_token(line + i)));
			if (tocken == 3 || tocken == 4)
				i += 2;
			else
				i++;
		}
		if (it_is_white_space(line[i]) == 0 && it_is_a_token(line[i]) == 0)
			its_a_word(lexer, ft_strdup(&line[i]), &i);
	 	while (line[i] && it_is_white_space(line[i]))
			i++;
	}
	return (0);
}

