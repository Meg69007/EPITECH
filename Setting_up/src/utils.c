/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** utils.c
*/

#include <stdlib.h>
#include "../my.h"

void free_grid(char **grid)
{
    int i = 0;

    while (grid[i]) {
        free(grid[i]);
        i++;
    }
    free(grid);
}

int min(int a, int b, int c)
{
    int min = (a < b) ? a : b;

    return ((min < c) ? min : c);
}

char **parse_grid(char *buffer, int expected_lines)
{
    char **grid = NULL;
    int i = 0;

    grid = malloc(sizeof(char *) * (expected_lines + 1));
    if (!grid)
        return (NULL);
    while (i < expected_lines) {
        grid[i] = get_next_line_from_buffer(&buffer);
        if (!grid[i])
            return (NULL);
        i++;
    }
    grid[i] = NULL;
    return (grid);
}
