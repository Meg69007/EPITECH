##
## EPITECH PROJECT, 2024
## delivery
## File description:
## Makefile
##

NAME = libhashtable.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
AR = ar
ARFLAGS = rcs

LIB_SRCS = \
  hash.c \
  new.c \
  delete.c \
  insert.c \
  search.c \
  dump.c \
  utils.c

LIB_OBJS = $(LIB_SRCS:.c=.o)

all: $(NAME) $(EXEC)

$(NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(LIB_OBJS)

$(EXEC): $(TEST_OBJS) $(NAME)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -lhashtable -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
