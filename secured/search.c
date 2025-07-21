/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** search.c
*/

#include <stdlib.h>
#include "hashtable.h"

char *ht_search(hashtable_t *ht, char *key)
{
    int hashed;
    int index;
    bucket_t *cur;

    if (!ht || !key || ht->len <= 0)
        return NULL;
    hashed = ht->hash(key, ht->len);
    index = hashed % ht->len;
    if (index < 0)
        index = -index;
    cur = ht->buckets[index];
    while (cur) {
        if (!my_strcmp(cur->key, key))
            return cur->value;
        cur = cur->next;
    }
    return NULL;
}
