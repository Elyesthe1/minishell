/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:59 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 17:10:48 by tovetouc         ###   ########.fr       */
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
void promt_start(t_lexer **lexer, t_env **env)
{
	char *config_promt;
	char *line;
	int i = 0;
	while (1)
	{
		if (i == 4)
			break;
		config_promt = promt_config();
		line = readline(config_promt);
		printf("line: %s\n", line);
		cmd_handler(line, env);
		// ft_lstadd_back(lexer, ft_lstnew(readline(config_promt)));
		free(config_promt);
		free(line);
		if (i++ == 4)
			break;	
	}
	lst_free(lexer);
 }
