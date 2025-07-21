/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** hash.c
*/

#include "hashtable.h"

int hash(char *key, int len)
{
    unsigned long h = 5381UL;
    unsigned char c;

    (void)len;
    while (*key) {
        c = (unsigned char)*key;
        key++;
        h = ((h << 5) + h) + c;
    }
    h &= 0xffffffffUL;
    return (int)h;
}
