/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** file_handling.c
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "../my.h"

int get_expected_lines(char *buffer, char **map_buffer)
{
    char *first_line = NULL;
    int expected_lines = 0;

    first_line = get_first_line(buffer);
    if (!first_line)
        return (-1);
    expected_lines = my_atoi(first_line);
    free(first_line);
    if (expected_lines <= 0)
        return (-1);
    *map_buffer = buffer;
    while (**map_buffer && **map_buffer != '\n')
        (*map_buffer)++;
    if (**map_buffer == '\n')
        (*map_buffer)++;
    return (expected_lines);
}

char *get_first_line(char *buffer)
{
    int i = 0;
    char *first_line = NULL;
    int j = 0;

    while (buffer[i] && buffer[i] != '\n')
        i++;
    first_line = malloc(i + 1);
    if (!first_line)
        return (NULL);
    for (j = 0; j < i; j++)
        first_line[j] = buffer[j];
    first_line[i] = '\0';
    return (first_line);
}

char *get_next_line_from_buffer(char **buffer)
{
    int len = 0;
    char *line = NULL;
    int i = 0;

    if (!(*buffer) || **buffer == '\0')
        return (NULL);
    while ((*buffer)[len] && (*buffer)[len] != '\n')
        len++;
    line = malloc(len + 1);
    if (!line)
        return (NULL);
    for (i = 0; i < len; i++)
        line[i] = (*buffer)[i];
    line[len] = '\0';
    *buffer += len;
    if (**buffer == '\n')
        (*buffer)++;
    return (line);
}

char **read_file(char const *filename)
{
    char *buffer = NULL;
    char *map_buffer = NULL;
    int expected_lines = 0;
    char **grid = NULL;

    buffer = read_file_to_buffer(filename);
    if (!buffer)
        return (NULL);
    expected_lines = get_expected_lines(buffer, &map_buffer);
    if (expected_lines <= 0) {
        free(buffer);
        return (NULL);
    }
    grid = parse_grid(map_buffer, expected_lines);
    free(buffer);
    return (grid);
}
