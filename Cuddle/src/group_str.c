/*
** EPITECH PROJECT, 2024
** ia
** File description:
** group_str.c
*/

#include "dataframe.h"

static int is_unique_in_array(char *str, char **arr, int n)
{
    int j = 0;

    for (j = 0; j < n; j++) {
        if (!strcmp(str, arr[j]))
            return (0);
    }
    return (1);
}

int unique_str_count(char **arr, int n)
{
    int count = 0;
    int i = 0;

    for (i = 0; i < n; i++) {
        if (is_unique_in_array(arr[i], arr, i))
            count++;
    }
    return (count);
}

static char **add_unique_str(char **ret, int *size, char *value)
{
    char **tmp = realloc(ret, sizeof(char *) * (*size + 1));

    if (!tmp) {
        return (NULL);
    }
    ret = tmp;
    ret[*size] = strdup(value);
    (*size)++;
    return (ret);
}

static int exists_in_ret(char **ret, int c, const char *str)
{
    int j = 0;

    for (j = 0; j < c; j++) {
        if (!strcmp(str, ret[j]))
            return (1);
    }
    return (0);
}

static int safe_add_unique_str(char ***ret_ptr, int *c, const char *str)
{
    char **tmp = add_unique_str(*ret_ptr, c, (char *)str);

    *ret_ptr = tmp;
    return (tmp != NULL);
}

char **unique_strs(char **arr, int n, int *out)
{
    char **ret = NULL;
    int c = 0;
    int i = 0;

    for (i = 0; i < n; i++) {
        if (exists_in_ret(ret, c, arr[i]))
            continue;
        if (!safe_add_unique_str(&ret, &c, arr[i]))
            return (NULL);
    }
    *out = c;
    return (ret);
}
