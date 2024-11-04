/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:02 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 18:00:51 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
#include <strings.h>


// 0 si pas un tockens 
// < == 1
// > == 2
// >> == 3
// << == 4
// | == 5

// int signal;


typedef struct s_tokens
{
	int		tocken;
}					t_tokens;

typedef struct s_env
{
	char			*str;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_parser
{
	char                    **str;
	// int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
}	t_parser;

void lst_printf(t_lexer *lexer);

//
int quote(char *loc, char **ligne);
int i_am_in_qote(int *qote);
int quote_checker1(char *line, int qote[2]);
int 	quote_checker(char *line);
int token_print_error();

void greed_line(int token, int *i);

void	ctrl_D(char *promt, char *line);
void    free_promt(char *line, char *promt, t_lexer **lexer);
int it_is_a_token(char c);
t_lexer	*ft_lstnewtoken(int content);
char	*ft_strdup(char *s);
t_env				*ft_lstlastenv(t_env *lst);
void				ft_lstadd_backenv(t_env **lst, t_env *new);
t_env				*ft_lstnewenv(void *content);
void				lst_freeenv(t_env **lexer);
int	*ft_strchr_tokens(char *str);
int it_is_white_space(char c);
void 	token_error(char *line, t_lexer **lexer, char *p);
int it_is_valid_token(char *s);
void set_signal_action(void);

int				lst_free(t_lexer **lexer);
// char				**ft_split(char *s, char c);
void				stock_env(char **env, t_env **ev);
t_lexer				*ft_lstnew(void *content, int i);
int				ft_lstadd_back(t_lexer **lst, t_lexer *new);
char				*ft_strjoin(char *s1, char *s2, int n);
char				*ft_strdup(char *s);
int					ft_free(char *s);
int					lexer_config(t_lexer **lexer, char *line);
int					ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				cmd_handler(char* cmd_name, t_env **env);
void				built_exit(int status);
void				built_pwd();
void				built_env(t_env **env);
void				built_echo(char *str, bool newline);
void				built_unset(char *env_name, t_env **env);
void				built_export(t_env **env);
void				promt_start(t_lexer **lexer, t_env **env);
int					ft_strcmp(const char *s1, const char *s2);
char				*get_env_name(char *str);
char				*get_env_value(char *str);
char				*ft_joinstrcpy(char *s1, char *s2, char *s3, int n);
char				*ft_strcpy(char *dest, char *src);

#endif
