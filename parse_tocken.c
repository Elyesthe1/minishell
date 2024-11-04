/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tocken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:03:08 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 18:03:07 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void greed_line(int token, int *i)
{
	if (token == 3 || token == 4)
		*i += 2;
	else
		*i += 1 ;
}

int i_am_in_qote(int *qote)
{
	if (qote[0] == 1 && qote[1] == 1)
		return (1);
	if (qote[0] == 0 && qote[1] == 1)
		return (1);
	if (qote[0] == 1 && qote[1] == 0)
		return (1);
	return (0);
}

int it_is_a_token(char c)
{

    if (c == '<')
        return (1);
    if (c == '>')
        return (2);
    if (c == '|')
        return (5);
    return (0);
}
int it_is_white_space(char c)
{
    if ((c >= 9 && c <= 13) || c == ' ')
        return (1);
    return (0);
}

int it_is_valid_token(char *s)
{
	int tocken;

	tocken = it_is_a_token(s[0]);
	if (tocken == 5)
	{
		if (it_is_a_token(s[1]) != 0)
			return (-5);
		return (51);
	}
	if (it_is_a_token(s[1]) == 0)
		return (tocken);
	if (tocken == it_is_a_token(s[1]))
	{
		if (it_is_a_token(s[2]) != 0)
			return (-1);
		if (tocken == 1)
			return (4);
		if (tocken == 2)
			return (3);
			
	}
	return (-2);
}
