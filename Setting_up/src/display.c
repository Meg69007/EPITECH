/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** display.c
*/

#include <unistd.h>
#include "../my.h"

void print_grid(char **grid)
{
    int i = 0;

    while (grid[i]) {
        write(1, grid[i], my_strlen(grid[i]));
        write(1, "\n", 1);
        i++;
    }
}

void print_error(char *message)
{
    int len = 0;

    while (message[len] != '\0')
        len++;
    write(2, message, len);
}

int is_valid_char(char c)
{
    if (c == '.' || c == 'o')
        return (1);
    return (0);
}
