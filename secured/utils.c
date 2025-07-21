/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** utils.c
*/

#include <unistd.h>
#include <stdlib.h>

static void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_strlen(const char *s)
{
    int len = 0;

    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *my_strdup(const char *s)
{
    int len = my_strlen(s);
    char *dup = malloc(len + 1);
    int i = 0;

    if (!dup)
        return NULL;
    while (i < len) {
        dup[i] = s[i];
        i++;
    }
    dup[len] = '\0';
    return dup;
}

int my_putstr(const char *str)
{
    if (!str)
        return -1;
    while (*str) {
        my_putchar(*str);
        str++;
    }
    return 0;
}

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    my_putchar((nb % 10) + '0');
    return 0;
}
