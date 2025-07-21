/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** new.c
*/

#include <stdlib.h>
#include "hashtable.h"

hashtable_t *new_hashtable(int (*hashFn)(char *, int), int len)
{
    hashtable_t *ht;
    int i = 0;

    if (len <= 0)
        len = 1;
    ht = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (!ht)
        return NULL;
    ht->buckets = (bucket_t **)malloc(sizeof(bucket_t *) * len);
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    while (i < len) {
        ht->buckets[i] = NULL;
        i++;
    }
    ht->len = len;
    ht->hash = hashFn;
    return ht;
}
