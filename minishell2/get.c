/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** get.c
*/


#include <stdlib.h>
#include "mysh.h"

char **dup_environment(char **envp)
{
    int old_count = count_env_line(envp);

    return deep_dup_env(envp, old_count + 1);
}

char *my_getenv(char **envp, const char *name)
{
    int idx = find_var_index(envp, name);
    int len = 0;

    if (idx < 0)
        return NULL;
    len = my_strlen(name);
    return &envp[idx][len + 1];
}
