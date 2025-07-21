/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my_strlen.c
*/
#include "../my.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return (i);
}
