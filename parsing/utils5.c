/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:00:57 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 12:02:29 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init(int index[2], int quote[2], int *heredoc)
{
	index[0] = 0;
	index[1] = 0;
	quote[0] = 0;
	quote[1] = 0;
	*heredoc = 0;
}

char	*expander1(char **s, int index[2], char **line)
{
	(*s)[index[1]] = '\0';
	free(*line);
	return (*s);
}

void	bigline1(int i[2], char *av, char c)
{
	if (c == '0')
	{
		i[0] += ft_strlen(av);
		i[1]++;
	}
	else
		i[1]++;
}
