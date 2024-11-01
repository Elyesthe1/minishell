SRCS = main.c\
	   promt.c\
	   utils.c\
	   lst.c\
	   lst1.c\
	   env.c\

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
