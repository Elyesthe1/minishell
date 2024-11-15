/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:56:38 by erahal            #+#    #+#             */
/*   Updated: 2024/11/15 15:54:17 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// 0 si pas un tokens
// < == 1 infile
// > == 2 outfile
// >> == 3 outfile
// << == 4 infile
// | == 5

extern int			g_status_code;
// int signal;
// CTRL-C == 0
// CTRL-D == 1
// CTRL-\ == 2

typedef struct s_tokens
{
	int				token;
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
	struct s_lexer	*next;
}					t_lexer;
typedef struct s_outfile
{
	char			**outfile;
	int				*flag;
	int				*fd;
}					t_outfile;

typedef struct s_infile
{
	char			**infile;
	int				*flag;
	int				*fd;
}					t_infile;

typedef struct s_parser
{
	char			**str;
	t_infile		infile;
	t_outfile		outfile;
	struct s_parser	*next;
}					t_parser;

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}					t_pids;


void				lst_printf(t_lexer *lexer, t_parser *parser);
//
void				ft_lstadd_backcmd(t_parser **lst, t_parser *new);
t_parser			*ft_lstnewcmd(t_lexer *lexer);
int					ft_isalnum(int n);
void				alloc(t_parser **parser, int infile, int outfile,
						t_lexer *lexer);
int					valid_dollar(char c);
int					free_zero(char *l);
void				last_status(char **s, int index[2]);
int					exit_status(void);
void				remove_from_env( t_env **env, char *env_name);

char				*var_name(char *line);
int					bigline(char *line, t_env **env, char *av);
void				remp(char **s, int index[2], char *line, t_env **env);
void				var_replace2(int index[2], char **s, char **line,
						int *heredoc);
void				var_replace1(int quote[2], int i);
int					ft_isdigit(int n);
int					valid_dollar(char c);

char				*var_name(char *line);
void				remp(char **s, int index[2], char *line, t_env **env);
void				var_replace1(int quote[2], int i);
int					ft_isdigit(int n);
void				lst_free_parser(t_parser **parser);
t_parser			*ft_lstlastcmd(t_parser *lst);
void				alloc1(t_lexer *lexer, t_parser **parser);
void				free_free(char **s);
void				fill2(t_lexer *lexer, t_parser **parser);
void				fill(t_parser **new, t_lexer *lexer, int size);
int					quote(char *loc, char **ligne);
int					in_quote(int *quote);
int					quote_checker1(char *line, int quote[2]);
int					quote_checker(char *line);
int					token_print_error(int n);
int					ft_strlen_quote_parse(char *s);
char				*ft_strtrim(char const *s1, char const *set);
void				text_parse_quote(t_lexer **lexer, char *s);
char				*get_env_name(char *str);
void				lst_free_parser(t_parser **parser);
void				how_much_cmd1(t_lexer **lexer, int *i, int n);
void				greed_line(int token, int *i);
void				ctrl_d(char *prompt, char *line);
void				free_all(char *line, char *prompt, t_lexer **lexer,
						t_parser **parser);
int					is_token(char c);
char				*expander(char **line, t_env **env, int heredoc, char *av);

t_lexer				*ft_lstnewt(int content);
char				*ft_strdup(char *s);
t_env				*ft_lstlastenv(t_env *lst);
void				ft_lstadd_backenv(t_env **lst, t_env *new);
t_env				*ft_lstnewenv(void *content);
void				lst_freeenv(t_env **lexer);
int					*ft_strchr_tokens(char *str);
int					is_ws(char c);
void				token_error(char *line, t_lexer **lexer, char *p);
int					is_valid_token(char *s);
void				set_signal_action(void);
void				signal_handler(int signal);
char				*ft_strjoin(char *s1, char *s2);
int					lst_free(t_lexer **lexer);
void				stock_env(char **env, t_env **ev);
t_lexer				*ft_lstnew(void *content);
int					ft_lstadd_back(t_lexer **lst, t_lexer *new);
char				*ft_strjoin_prompt(char *s1, char *s2, int n);
char				*ft_strdup(char *s);
int					ft_free(char *s);
int					lexer_config(t_lexer **lexer, char *line,
						t_parser **parser);
int					ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				cmd_handler(char *cmd_name, t_env **env);
int					built_exit(char **args, int ouside_fork);
int					built_pwd(t_env **env);
int					built_env(t_env **env);
int					built_echo(char **args);
int					built_unset(char **args, t_env **env);
int					built_export(char **args, t_env **env);
void				prompt_start(t_lexer **lexer, t_env **env, char *av);
int					ft_strcmp(const char *s1, const char *s2);
char				*get_env_name(char *str);
int					exec_outside_built(char **args, t_env **env);
char				*get_env_value(char *str);
char				*ft_joinstrcpy(char *s1, char *s2, char *s3, int n);
char				*ft_strcpy(char *dest, char *src);
char				*env_lst_to_str(t_env **env);
bool				exists_in_env(t_env **env, char *env_name);
int					built_cd(char **args, t_env **env);
void				add_to_env(t_env **env, char *env_name, char *env_value);
void				change_env_value(t_env **env, char *env_name,
						char *env_value);
int					executor(t_env **env, t_parser *parser, int n_pipes);
char				*get_command_path(char *command_name, t_env *env);
char				*construct_command_path(char *path, char *command_name);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **split);
char				**get_env_path(t_env *env);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				**convert_env_to_envp(t_env *env);
int					get_env_size(t_env *env);
int					replace_command_name_by_path(char **str, t_env *env);
void				add_pid(t_pids **pids, pid_t pid);
void				free_all_pids(t_pids **pids);
void				wait_all_pids(t_pids **pids);
int					here_doc(char *limiter, t_env **env, char *line, t_parser **parser);
char				*ft_strjoin_free(char *s1, char const *s2);
int					is_builtin(char *cmd_name);
void				execute_builtin(char *cmd_name, char **args, t_env **env);
t_env				*get_env_node(t_env **env, char *env_name, int n);
char				*ft_itoa(int n);
char				*get_next_line(int fd);
void				ft_bzero(void *s1, size_t n);
char				*ft_strncpy(char *str, char *s2, char c);
char				*ft_strdup(char *s);
int					ft_free_line(char *s);
char				*ft_strcpyv2(char *s1, char *s2, char *s3);
char				*ft_strjoin_line(char *s1, char *s2);
char				*ft_split_line(char *tab, char c);

int					exec_built(char **args, t_env **env);
t_env				*get_env_node(t_env **env, char *env_name, int n);
int					execute_outside_fork(char *cmd_name, char **args, int nb_of_pipes);
int					ft_isint(char *str);
int					ft_atoi(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					args_size(char **args);
char				*ft_strchr(const char *s, int c);
void				export_to_env(t_env **env, char **env_name,
						char **env_value);
int					manage_export(char **args, t_env **env);
void				create_pipe(int pipefd[2], t_parser **parser);
void				close_free_fd(t_parser **parser);
void				close_next_fd(t_parser **parser);

#endif
