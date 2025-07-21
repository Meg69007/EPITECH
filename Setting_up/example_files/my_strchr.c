/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my_strchr.c
*/
#include <stddef.h>
#include "../my.h"

char *my_strchr(const char *str, int c)
{
    while (*str) {
        if (*str == (char)c)
            return ((char *)str);
        str++;
    }
    if (c == '\0')
        return ((char *)str);
    return (NULL);
}
