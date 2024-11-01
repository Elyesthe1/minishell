/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:35 by tovetouc          #+#    #+#             */
/*   Updated: 2024/10/31 15:20:02 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "unistd.h"

// TODO: CHANGE THIS LATER TO TAKE INTO ACCOUNT CD
char	*built_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
}

// int	main(void)
// {
// 	char	*str;
	
// 	str = pwd();
// 	printf("%s\n", str);
// 	return (0);
// }
