/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** dump.c
*/

#include <unistd.h>
#include "hashtable.h"

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static void my_put_nbr_unsigned(unsigned int nb)
{
    if (nb >= 10)
        my_put_nbr_unsigned(nb / 10);
    my_putchar((nb % 10) + '0');
}

static void dump_bucket(bucket_t *cur, int (*hashfn)(char *, int), int size)
{
    unsigned int val;

    while (cur) {
        val = (unsigned int)hashfn(cur->key, size);
        my_putstr("> ");
        my_put_nbr_unsigned(val);
        my_putstr(" - ");
        my_putstr(cur->value);
        my_putstr("\n");
        cur = cur->next;
    }
}

void ht_dump(hashtable_t *ht)
{
    int i;

    if (!ht)
        return;
    for (i = 0; i < ht->len; i++) {
        my_putstr("[");
        my_put_nbr(i);
        my_putstr("]:\n");
        dump_bucket(ht->buckets[i], ht->hash, ht->len);
    }
}
