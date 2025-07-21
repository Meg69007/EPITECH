/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** insert.c
*/

#include <stdlib.h>
#include "hashtable.h"

bucket_t *find_b(bucket_t *head, char *key)
{
    while (head) {
        if (my_strcmp(head->key, key) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

bucket_t *make(char *key, char *value)
{
    bucket_t *b = malloc(sizeof(bucket_t));

    if (!b)
        return NULL;
    b->key = my_strdup(key);
    b->value = my_strdup(value);
    b->next = NULL;
    return b;
}

int get_index(hashtable_t *ht, char *key)
{
    int hashed;
    int idx;

    if (!ht || ht->len <= 0) {
        return 0;
    }
    hashed = ht->hash(key, ht->len);
    idx = hashed % ht->len;
    if (idx < 0)
        idx = -idx;
    return idx;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int index;
    bucket_t *existing;
    bucket_t *newb;
    if (!ht || !key || !value)
        return -1;
    if (ht->len <= 0)
        return -1;
    index = get_index(ht, key);
    existing = find_b(ht->buckets[index], key);
    if (existing) {
        free(existing->value);
        existing->value = my_strdup(value);
        return 0;
    }
    newb = make(key, value);
    if (!newb)
        return -1;
    newb->next = ht->buckets[index];
    ht->buckets[index] = newb;
    return 0;
}
