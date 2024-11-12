SRCS = main.c\
	   prompt.c\
	   utils.c\
	   utils1.c\
	   lst.c\
	   env/env1.c\
	   env/env2.c\
	   parser.c\
	   parse_token.c\
	   builtins/echo.c\
	   builtins/env.c\
	   builtins/exit.c\
	   builtins/export.c\
	   builtins/pwd.c\
	   builtins/unset.c\
	   builtins/cd.c\
	   commands/handler.c\
	   str/cmp.c\
	   str/cpy.c\
	   signal.c\
	   parse_quote.c\
	   utils3.c\
	   utils2.c\
	   lst2.c\
	   lst1.c\
	   commands/executor.c\
	   commands/cmd_utils.c\
	   str/split.c\
	   mem.c\
	   env/env3.c\
	   commands/pids.c\
	   commands/here_doc.c\
	   expander.c\
	   utils4.c\
	   ft_atoi.c\
	   str/put.c\
	   str/chr.c\
	   builtins/export_utils.c\
	   commands/executor_utils.c

CC = cc
RM = rm -f
FLAGS = -Wall  -Wextra -g -fsanitize=address #-Werror
NAME = minishell
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lreadline

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean 
