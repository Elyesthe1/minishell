/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:52 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 17:49:37 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_checker1(char *line, int qote[2])
{
	int i;

	i = 0;
	while (line[i])
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
	if (qote[0] == 1 || qote[1] == 1)
		return (1);
	return (0);
}

int 	quote_checker(char *line)
{
	int qote[2];
	int i;

	i = 0;
	qote[0] = 0;
	qote[1] = 0;
	if (quote_checker1(line, qote) == 1)
	{
		write(2, "bash: unexpected while looking for matching quote\n", 51);
		return (1);
	}
	return (0);
}
