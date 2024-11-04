SRCS = main.c\
	   promt.c\
	   utils.c\
	   utils1.c\
	   lst.c\
	   lst1.c\
	   env.c\
	   parser.c\
	   parse_tocken.c\
	   builtins/echo.c\
	   builtins/env.c\
	   builtins/exit.c\
	   builtins/export.c\
	   builtins/pwd.c\
	   builtins/unset.c\
	   commands/handler.c\
	   str/cmp.c\
	   str/cpy.c\
	   signal.c\
	   parse_qote.c\
	   write_error.c\


CC = cc
RM = rm -f
FLAGS = -Wall  -Wextra -g  #-fsanitize=address  #-Werror
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
