SRCS = main.c\
	   promt.c\
	   utils.c\
	   utils1.c\
	   lst.c\
	   lst1.c\
	   env.c\
	   parser.c\
	   parse_tocken.c\
<<<<<<< HEAD
	   signal.c\
=======
	   builtins/echo.c\
	   builtins/env.c\
	   builtins/exit.c\
	   builtins/export.c\
	   builtins/pwd.c\
	   builtins/unset.c\
	   commands/handler.c\
	   str/cmp.c\
	   str/cpy.c
>>>>>>> 95d67e54b9c070708fb8c6457eca95a729ed1dcf

CC = cc
RM = rm -f
FLAGS = -Wall  -Wextra -g  -fsanitize=address  #-Werror
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
