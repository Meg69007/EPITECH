/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** utils.c
*/

#include <unistd.h>
#include <string.h>
#include "mysh.h"

void my_puterr(const char *msg)
{
    if (msg == NULL)
        return;
    write(2, msg, my_strlen(msg));
}

int my_strlen(const char *s)
{
    int i = 0;

    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *my_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    if (!dest || !src)
        return dest;
    while (dest[i])
        i++;
    while (src[j]) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strchr(const char *s, int c)
{
    int i = 0;

    if (!s)
        return 0;
    while (s[i]) {
        if (s[i] == c)
            return (char *)&s[i];
        i++;
    }
    if (!c)
        return (char *)&s[i];
    return 0;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return 0;
    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
