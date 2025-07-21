##
## EPITECH PROJECT, 2024
## delivery
## File description:
## makefile
##

NAME    =   my_ls

SRC_DIR =   src
LIB_DIR =   lib
INC_DIR =   include

SRC     =   $(SRC_DIR)/main.c \
            $(SRC_DIR)/dir_utils.c \
            $(SRC_DIR)/display_utils.c \
            $(SRC_DIR)/entry.c \
            $(SRC_DIR)/entry_utils.c \
            $(SRC_DIR)/path_utils.c \
            $(SRC_DIR)/options.c \
            $(SRC_DIR)/process.c \
            $(SRC_DIR)/time_utils.c

LIB     =   $(LIB_DIR)/my_putchar.c \
            $(LIB_DIR)/my_putstr.c \
            $(LIB_DIR)/my_put_nbr.c \
            $(LIB_DIR)/my_strlen.c \
            $(LIB_DIR)/my_strcpy.c \
            $(LIB_DIR)/my_strcat.c \
            $(LIB_DIR)/my_strcmp.c \
            $(LIB_DIR)/mem.c

OBJ     =   $(SRC:.c=.o)
LIB_OBJ =   $(LIB:.c=.o)

CFLAGS  =   -W -Wall -Wextra -I $(INC_DIR)
CC      =   gcc

LIB_NAME =  libmy.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB_NAME)
	$(CC) -o $(NAME) $(OBJ) -L. -lmy

$(LIB_NAME): $(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
