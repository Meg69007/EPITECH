/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** hashtable.h
*/

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef HASHTABLE_H
    #define HASHTABLE_H

typedef struct bucket_s {
    char *key;
    char *value;
    struct bucket_s *next;
} bucket_t;

typedef struct hashtable_s {
    bucket_t **buckets;
    int len;
    int (*hash)(char *key, int len);
} hashtable_t;

int my_strlen(char *s);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *s);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int hash(char *key, int len);
hashtable_t *new_hashtable(int (*hashFn)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);
int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);

#endif
