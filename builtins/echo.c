/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:16:07 by tovetouc          #+#    #+#             */
/*   Updated: 2024/10/31 15:18:59 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo(char *str, int newline)
{
	printf("%s", str);
	if (newline)
		printf("\n");
}

int main(int argc, char **argv)
{
	echo(argv[1], 0);
	return (0);
}
