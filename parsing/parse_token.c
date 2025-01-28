/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:56:09 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 12:38:49 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	greed_line(int token, int *i)
{
	if (token == 3 || token == 4)
		*i += 2;
	else
		*i += 1;
}

int	is_token(char c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (2);
	if (c == '|')
		return (5);
	return (0);
}

int	is_ws(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_valid_token1(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] == '\0')
		return (2);
	if (is_token(s[i]) != 0)
		return (-1);
	return (0);
}

int	is_valid_token(char *s)
{
	int	token;
	int	i;

	i = 1;
	token = is_token(s[0]);
	if (token == 5)
	{
		while (s[i] && is_ws(s[i]))
			i++;
		if (is_token(s[i]) == 5 || s[i] == '\0')
			return (-5);
		return (5);
	}
	if (is_token(s[1]) == 0 && is_valid_token1(s + 1) == 0)
		return (token);
	if (token == is_token(s[1]))
	{
		if (is_token(s[2]) != 0 || is_valid_token1(s + 2) != 0)
			return (-1);
		if (token == 1 || is_valid_token1(s + 2) != 0)
			return (4);
		if (token == 2 || is_valid_token1(s + 2) != 0)
			return (3);
	}
	return (-2);
}
