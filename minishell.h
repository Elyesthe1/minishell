/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:02 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 16:12:03 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// 0 si pas un tockens 
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
}	t_simple;

void lst_printf(t_lexer *lexer);

//
int it_is_a_token(char c);
t_lexer	*ft_lstnewtoken(int content);
char	*ft_strdup(char *s);
int ft_strlen(char *s);

t_env				*ft_lstlastenv(t_env *lst);
void				ft_lstadd_backenv(t_env **lst, t_env *new);
t_env				*ft_lstnewenv(void *content);
void				lst_freeenv(t_env **lexer);
int lexer_config(t_lexer **lexer, char *line);
int	*ft_strchr_tokens(char *str);
int it_is_white_space(char c);
void 	token_error(char *line, t_lexer **lexer, char *p);
int it_is_valid_token(char *s);

int				lst_free(t_lexer **lexer);
// char				**ft_split(char *s, char c);
void				stock_env(char **env, t_env **ev);
t_lexer				*ft_lstnew(void *content, int i);
int				ft_lstadd_back(t_lexer **lst, t_lexer *new);
void				promt_start(t_lexer **lexer);
char				*ft_strjoin(char *s1, char *s2, int n);
char				*ft_strdup(char *s);
int					ft_free(char *s);

#endif
