/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my_strtok.c
*/
#include "../my.h"
#include <stddef.h>

char *move_to_next(char *str, const char *delim)
{
    while (*str && my_strchr(delim, *str))
        str++;
    return (*str ? str : NULL);
}

char *find_last(char *start, const char *delim)
{
    while (*start && !my_strchr(delim, *start))
        start++;
    return (start);
}

char *update_save(char *end)
{
    if (*end) {
        *end = '\0';
        return (end + 1);
    }
    return (NULL);
}

char *my_strtok(char *str, const char *delim)
{
    static char *saved_str = NULL;
    char *start;
    char *end;

    if (str)
        saved_str = str;
    if (!saved_str)
        return (NULL);
    start = move_to_next(saved_str, delim);
    if (!start) {
        saved_str = NULL;
        return (NULL);
    }
    end = find_last(start, delim);
    saved_str = update_save(end);
    return (start);
}
