/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** delete.c
*/

#include <stdlib.h>
#include "hashtable.h"

void delete_hashtable(hashtable_t *ht)
{
    int i = 0;
    bucket_t *cur;
    bucket_t *tmp;

    if (!ht)
        return;
    while (i < ht->len) {
        cur = ht->buckets[i];
        while (cur) {
            tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
        i++;
    }
    free(ht->buckets);
    free(ht);
}

bucket_t *find(bucket_t *head, char *key, bucket_t **prev)
{
    bucket_t *cur = head;

    *prev = NULL;
    while (cur) {
        if (!my_strcmp(cur->key, key))
            return cur;
        *prev = cur;
        cur = cur->next;
    }
    return NULL;
}

void remove_bucket(bucket_t **head, bucket_t *cur, bucket_t *prev)
{
    if (!prev)
        *head = cur->next;
    else
        prev->next = cur->next;
    free(cur->key);
    free(cur->value);
    free(cur);
}

int do_delete(bucket_t **head, char *key)
{
    bucket_t *cur = *head;
    bucket_t *prev = NULL;

    while (cur) {
        if (!my_strcmp(cur->key, key)) {
            remove_bucket(head, cur, prev);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hashed;
    int index;

    if (!ht || !key || ht->len <= 0)
        return -1;
    hashed = ht->hash(key, ht->len);
    index = hashed % ht->len;
    if (index < 0)
        index = -index;
    return do_delete(&(ht->buckets[index]), key) ? 0 : -1;
}
