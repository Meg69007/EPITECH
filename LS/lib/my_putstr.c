/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my_putstr.c
*/


#include "../my.h"
#include "unistd.h"
#include "stdio.h"

int my_putstr(char const *str)
{
    if (str == NULL) {
        return -1;
    }
    while (*str != '\0') {
        my_putchar(*str);
        str++;
    }
    return 0;
}
