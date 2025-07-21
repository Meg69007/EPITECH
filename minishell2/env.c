/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** env.c
*/

#include <stdlib.h>
#include "mysh.h"

char **deep_dup_env(char **envp, int new_size)
{
    int old_count = count_env_line(envp);
    int copy_count = old_count;
    char **res = NULL;
    int idx = 0;

    if ((new_size - 1) < copy_count)
        copy_count = new_size - 1;
    res = allocate_new_env(new_size);
    if (!res)
        return NULL;
    while (idx < copy_count) {
        res[idx] = my_strdup_safe(envp[idx]);
        if (!res[idx]) {
            partial_free_array(res, idx);
            return NULL;
        }
        idx++;
    }
    return res;
}

static char *build_line(const char *name, const char *value)
{
    int size = my_strlen(name) + my_strlen(value) + 2;
    char *lin = malloc(size);
    int i = 0;

    if (!lin)
        return NULL;
    while (i < size) {
        lin[i] = '\0';
        i++;
    }
    my_strcat(lin, name);
    my_strcat(lin, "=");
    my_strcat(lin, value);
    return lin;
}

int find_var_index(char **envp, const char *name)
{
    int i = 0;
    int len = 0;

    if (!envp || !name)
        return -1;
    len = my_strlen(name);
    while (envp[i]) {
        if (!my_strncmp(envp[i], name, len) && envp[i][len] == '=')
            return i;
        i++;
    }
    return -1;
}

static int replace_line(char ***envp, int idx, char *newline, char **dup)
{
    free(dup[idx]);
    dup[idx] = newline;
    free_array(*envp);
    *envp = dup;
    return 0;
}

static int do_update_var(char ***envp, int old_count, int var_index, char *lin)
{
    char **dup = deep_dup_env(*envp, old_count + 1);

    if (!dup) {
        free(lin);
        return -1;
    }
    return replace_line(envp, var_index, lin, dup);
}

static int do_append_var(char ***envp, int old_count, char *lin)
{
    char **dup = deep_dup_env(*envp, old_count + 2);

    if (!dup) {
        free(lin);
        return -1;
    }
    dup[old_count] = lin;
    free_array(*envp);
    *envp = dup;
    return 0;
}

int set_env_var_deep(char ***envp, const char *name, const char *value)
{
    int old_count = 0;
    int idx = 0;
    char *lin = NULL;

    if (!envp || !(*envp) || !name || !value)
        return -1;
    old_count = count_env_line(*envp);
    idx = find_var_index(*envp, name);
    lin = build_line(name, value);
    if (!lin)
        return -1;
    if (idx >= 0)
        return do_update_var(envp, old_count, idx, lin);
    return do_append_var(envp, old_count, lin);
}

static int handle_single_var_env(char ***envp)
{
    free_array(*envp);
    *envp = allocate_new_env(1);
    if (!*envp)
        return -1;
    return 0;
}

static int rebuild_env_no_var(char ***envp, int old_count, int var_index)
{
    char **dup = malloc(sizeof(char *) * old_count);
    int ret = 0;

    if (!dup)
        return -1;
    ret = copy_skip_idx(envp, dup, old_count, var_index);
    if (ret < 0) {
        free_array(*envp);
        return -1;
    }
    free_array(*envp);
    *envp = dup;
    return 0;
}

int unset_env_var_deep(char ***envp, const char *name)
{
    int old_count = 0;
    int idx = 0;

    if (!envp || !(*envp) || !name)
        return -1;
    old_count = count_env_line(*envp);
    idx = find_var_index(*envp, name);
    if (idx < 0)
        return 0;
    if (old_count <= 1)
        return handle_single_var_env(envp);
    return rebuild_env_no_var(envp, old_count, idx);
}
