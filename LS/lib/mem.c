/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** lib.c
*/

#include "../my.h"

void *my_memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned int i = 0;
    char *d = dest;
    const char *s = src;

    while (i < n) {
        d[i] = s[i];
        i++;
    }
    return dest;
}
