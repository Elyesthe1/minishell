SRCS = main.c\
	   parsing/prompt.c\
	   parsing/utils.c\
	   parsing/utils1.c\
	   parsing/lst.c\
	   env/env1.c\
	   env/env2.c\
	   parsing/parser.c\
	   parsing/parse_token.c\
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
	   parsing/signal.c\
	   parsing/parse_quote.c\
	   parsing/utils3.c\
	   parsing/utils2.c\
	   parsing/lst2.c\
	   parsing/lst1.c\
	   commands/executor.c\
	   commands/cmd_utils.c\
	   commands/executor_utils.c\
	   str/split.c\
	   str/put.c\
	   str/chr.c\
	   utils/ft_atoi.c\
	   utils/mem.c\
	   env/env3.c\
	   commands/pids.c\
	   commands/here_doc.c\
	   builtins/export_utils.c\
	   parsing/expander.c\
	   parsing/utils4.c\
	   builtins/export_sort.c\
	   parsing/utils5.c\

CC = cc
RM = rm -f
FLAGS = -Wall -Werror 	-Wextra 
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
