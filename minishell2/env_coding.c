/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** env_coding.c
*/

#include <stdlib.h>
#include "mysh.h"

static int skip_env_line(char ***envp, int *i)
{
    (void)envp;
    (*i)++;
    return 0;
}

static int copy_env_line(char ***envp, char **dup, int *i, int *j)
{
    dup[*j] = my_strdup_safe((*envp)[*i]);
    if (!dup[*j])
        return partial_free_array(dup, *j);
    (*j)++;
    (*i)++;
    return 0;
}

int copy_skip_idx(char ***envp, char **dup, int old_count, int var_ind)
{
    int i = 0;
    int j = 0;
    int ret = 0;

    while (i < old_count) {
        if (i == var_ind)
            ret = skip_env_line(envp, &i);
        else
            ret = copy_env_line(envp, dup, &i, &j);
        if (ret < 0)
            return -1;
    }
    dup[j] = NULL;
    return 0;
}
