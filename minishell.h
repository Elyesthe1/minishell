/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:02 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 10:45:49 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_lexer
{
	char    	*str;
	// t_tokens        token;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;
void lst_free(t_lexer **lexer);

t_lexer	*ft_lstnew(void *content);
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
void promt_start(t_lexer **lexer);
char	*ft_strjoin(char *s1, char *s2, int n);
char	*ft_strdup(char *s);
int ft_free(char *s);







#endif
