/*
** EPITECH PROJECT, 2024
** piscine
** File description:
** my_putchar.c
*/

#include <unistd.h>
#include "../my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_puterror(const char *str)
{
    int len = 0;

    while (str[len])
        len++;
    write(2, str, len);
}
