/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** other_utils.c
*/

#include "mysh.h"
#include <stdlib.h>

char *my_strdup(const char *src)
{
    int len = 0;
    char *dest;
    int i = 0;

    if (!src)
        return 0;
    while (src[len])
        len++;
    dest = malloc(len + 1);
    if (!dest)
        return 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return dest;
}

int my_atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    if (!str)
        return 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (!dest || !src)
        return dest;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    if (!s1 || !s2 || n <= 0)
        return 0;
    while (s1[i] && s2[i] && i < n - 1) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

int my_strcmp_len(const char *s1, const char *s2, int len)
{
    int i = 0;

    if (!s1 || !s2 || len <= 0)
        return -1;
    while (i < len && s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i < len)
        return (s1[i] - s2[i]);
    return 0;
}
