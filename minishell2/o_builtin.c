/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** o_builtin.c
*/

#include <ctype.h>
#include <stdlib.h>
#include "mysh.h"

static int is_valid_name(const char *name)
{
    int i = 0;

    if (!name[0] || (!isalpha((unsigned char)name[0]) && name[0] != '_'))
        return 0;
    for (i = 1; name[i]; i++) {
        if (!isalnum((unsigned char)name[i]) && name[i] != '_')
            return 0;
    }
    return 1;
}

int builtin_setenv(char **args, char ***env)
{
    if (!args[1]) {
        builtin_env(args, *env);
        return 0;
    }
    if (!is_valid_name(args[1])) {
        my_puterr("setenv: Invalid variable name.\n");
        return 0;
    }
    if (!args[2]) {
        if (set_env_var_deep(env, args[1], "") < 0)
            my_puterr("setenv: error.\n");
        return 0;
    }
    if (args[3]) {
        my_puterr("setenv: Too many arguments.\n");
        return 0;
    }
    if (set_env_var_deep(env, args[1], args[2]) < 0)
        my_puterr("setenv: error.\n");
    return 0;
}

int builtin_unsetenv(char **args, char ***env)
{
    if (!args[1]) {
        my_puterr("unsetenv: Too few arguments.\n");
        return 0;
    }
    if (args[2]) {
        my_puterr("unsetenv: Too many arguments.\n");
        return 0;
    }
    if (unset_env_var_deep(env, args[1]) < 0)
        my_puterr("unsetenv: error.\n");
    return 0;
}

int builtin_exit(char **args)
{
    int code = 0;

    if (args[1])
        code = my_atoi(args[1]);
    exit(code);
}
