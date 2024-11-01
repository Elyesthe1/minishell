/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:59 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 14:07:06 by erahal           ###   ########.fr       */
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
		if (i == 4)
			break;
		config_promt = promt_config();
		ft_lstadd_back(lexer, ft_lstnew(readline(config_promt)));
		free(config_promt);
		if (i++ == 4)
			break;	
	}
	lst_free(lexer);
 }
