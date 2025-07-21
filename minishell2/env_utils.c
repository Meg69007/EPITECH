/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** env_utils.c
*/

#include <stdlib.h>
#include "mysh.h"

int count_env_line(char **envp)
{
    int i = 0;

    if (!envp)
        return 0;
    while (envp[i])
        i++;
    return i;
}

void free_array(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *my_strdup_safe(const char *src)
{
    char *dest = NULL;
    int len = my_strlen(src);
    int i = 0;

    dest = malloc(len + 1);
    if (!dest)
        return NULL;
    while (i < len) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int partial_free_array(char **arr, int limit)
{
    int idx = 0;

    while (idx < limit) {
        free(arr[idx]);
        idx++;
    }
    free(arr);
    return -1;
}

char **allocate_new_env(int size)
{
    char **res = NULL;
    int i = 0;

    res = malloc(sizeof(char *) * size);
    if (!res)
        return NULL;
    while (i < size) {
        res[i] = NULL;
        i++;
    }
    return res;
}
