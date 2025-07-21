/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my_strdup.c
*/

#include <stdlib.h>
#include "../my.h"

char *my_strdup(const char *str)
{
    int len = 0;
    char *dup;

    while (str[len])
        len++;
    dup = malloc((len + 1) * sizeof(char));
    if (!dup)
        return (NULL);
    for (int i = 0; i < len; i++)
        dup[i] = str[i];
    dup[len] = '\0';
    return (dup);
}
