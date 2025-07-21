##
## EPITECH PROJECT, 2025
## LIBCUDDLE
## File description:
## Makefile
##

NAME    =   libcuddle.a

SRC_DIR =   src

INC_DIR =   include

SRC     =   $(SRC_DIR)/utils_s.c       \
            $(SRC_DIR)/read.c          \
            $(SRC_DIR)/write.c         \
            $(SRC_DIR)/head.c          \
            $(SRC_DIR)/tail.c          \
            $(SRC_DIR)/shape.c         \
            $(SRC_DIR)/info.c          \
            $(SRC_DIR)/describe.c      \
            $(SRC_DIR)/filter.c        \
            $(SRC_DIR)/sort.c          \
            $(SRC_DIR)/group.c         \
            $(SRC_DIR)/apply.c         \
            $(SRC_DIR)/type.c          \
            $(SRC_DIR)/group_fill.c    \
            $(SRC_DIR)/group_str.c     \
            $(SRC_DIR)/value.c         \
            $(SRC_DIR)/utils_d.c       \
            $(SRC_DIR)/free.c

OBJ     =   $(SRC:.c=.o)

CFLAGS  =   -Wall -Wextra -I$(INC_DIR)
LDFLAGS =   -lm

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
