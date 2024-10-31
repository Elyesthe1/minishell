/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:59 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 11:00:18 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *promt_config()
{
	char *user;
	char *session;
	char *cwd;
	char *s;
	int i;

	i = 0;
	user = getenv("USER");
	if (user == NULL)
		return ("minishell");
	session = getenv("SESSION_MANAGER");
	if (session == NULL)
		return ("minishell");
	while (*(session - 1) != '/')
		session++;	
	while (session[i] != '.')
		i++;
	session[i] = '\0';
	s = ft_strjoin(user, session, 2);
	cwd = getcwd(NULL, 0);
	s = ft_strjoin(s, cwd, 1);
	return (ft_strjoin(s, " ", 0));
}
void promt_start(t_lexer **lexer)
{
	char *config_promt;
	int i = 0;
	while (1)
	{
		if (i == 3)
			break;
		config_promt = promt_config();
		// readline(config_promt);
		ft_lstadd_back(lexer, ft_lstnew(readline(config_promt)));
		// printf("%s %d\n", (*lexer)->str, (*lexer)->i);
		free(config_promt);
		i++;
	}
	// while ((*lexer))
	// {
	// 	printf("%s %d\n", (*lexer)->str, (*lexer)->i);
	// 	(*lexer) = (*lexer)->next;
	// }
	// (*lexer) = (*lexer)->next;
	// printf("%s \n", (*lexer)->str);

	// (*lexer) = (*lexer)->prev;
	// while (lexer)
	// {
	// 	printf("%s\n", lexer->str);
	// 	lexer = lexer->prev;
	// }
	lst_free(lexer);
 }
