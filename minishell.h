/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:02 by erahal            #+#    #+#             */
/*   Updated: 2024/10/31 15:33:25 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// < == 1
// > == 2
// >> == 3
// << == 4
// | == 5

typedef struct s_tokens
{
	int		tocken;
}					t_tokens;

typedef struct s_env
{
	char			*str;
	char			*var_env;
	struct s_env	*next;
}					t_env;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_simple_cmds
{
	char                    **str;
	// int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple;

t_env				*ft_lstlastenv(t_env *lst);
void				ft_lstadd_backenv(t_env **lst, t_env *new);
t_env				*ft_lstnewenv(void *content);
void				lst_freeenv(t_env **lexer);

void				lst_free(t_lexer **lexer);
char				**ft_split(char *s, char c);
void				stock_env(char **env, t_env **ev);
t_lexer				*ft_lstnew(void *content);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
void				promt_start(t_lexer **lexer);
char				*ft_strjoin(char *s1, char *s2, int n);
char				*ft_strdup(char *s);
int					ft_free(char *s);

#endif
