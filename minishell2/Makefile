##
## EPITECH PROJECT, 2024
## delivery
## File description:
## makefile
##

CC      = gcc
CFLAGS  = -Wall -Wextra -I. -g
NAME    = mysh

SRC     = main.c       \
          shell_loop.c \
          other_utils.c \
          env.c \
          env_coding.c \
          o_builtin.c \
          o_exec.c \
          builtin.c   \
          exec.c   \
          env_utils.c  \
          pipe.c \
          parser.c \
          redirect.c \
          get.c \
          parse.c \
          parse_line_utils.c \
          parse_pipe.c \
          utils.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
