/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** mag_generate.c
*/

#include <stdlib.h>
#include "../my.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int result = 0;

    if (!str)
        return (-1);
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

char *generate_line(int size, char *pattern)
{
    char *line = NULL;
    int pattern_len = 0;

    if (!pattern)
        return (NULL);
    pattern_len = my_strlen(pattern);
    if (pattern_len == 0)
        return (NULL);
    line = malloc(sizeof(char) * (size + 1));
    if (!line)
        return (NULL);
    fill_line(line, size, pattern, pattern_len);
    return (line);
}

void fill_line(char *line, int size, char *pattern, int pattern_len)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        line[i] = pattern[j];
        j++;
        if (j >= pattern_len)
            j = 0;
    }
    line[size] = '\0';
}

char **generate_map(char **argv)
{
    int size = 0;
    char **grid = NULL;
    int i = 0;

    size = my_getnbr(argv[1]);
    if (size <= 0)
        return (NULL);
    grid = malloc(sizeof(char *) * (size + 1));
    if (!grid)
        return (NULL);
    for (i = 0; i < size; i++) {
        grid[i] = generate_line(size, argv[2]);
        if (!grid[i]) {
            free_grid(grid);
            return (NULL);
        }
    }
    grid[size] = NULL;
    return (grid);
}

int check_line_lengths(char **grid)
{
    int i = 0;
    int line_length = 0;

    if (!grid || !grid[0])
        return (84);
    line_length = my_strlen(grid[0]);
    while (grid[i]) {
        if (my_strlen(grid[i]) != line_length)
            return (84);
        i++;
    }
    return (0);
}
