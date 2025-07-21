/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** builtin.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

int builtin_cd(char **args, char ***env)
{
    char *home = NULL;

    if (!args[1]) {
        home = my_getenv(*env, "HOME");
        if (!home) {
            my_puterr("cd: HOME not set\n");
            return 0;
        }
        if (chdir(home) != 0)
            my_puterr("cd: cannot change directory.\n");
        return 0;
    }
    if (chdir(args[1]) != 0)
        my_puterr("cd: cannot change directory.\n");
    return 0;
}

int builtin_env(char **args, char **env)
{
    int i = 0;

    if (args[1]) {
        my_puterr("env: no arguments supported.\n");
        return 0;
    }
    while (env[i]) {
        write(1, env[i], my_strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}

int is_builtin_command(const char *cmd)
{
    if (!cmd)
        return 0;
    if (!my_strcmp(cmd, "cd") || !my_strcmp(cmd, "env") ||
        !my_strcmp(cmd, "setenv") || !my_strcmp(cmd, "unsetenv") ||
        !my_strcmp(cmd, "exit"))
        return 1;
    return 0;
}

static int handle_group1(char **args, char ***env)
{
    if (!my_strcmp(args[0], "cd"))
        return builtin_cd(args, env);
    if (!my_strcmp(args[0], "env"))
        return builtin_env(args, *env);
    return -1;
}

static int handle_group2(char **args, char ***env)
{
    if (!my_strcmp(args[0], "setenv"))
        return builtin_setenv(args, env);
    if (!my_strcmp(args[0], "unsetenv"))
        return builtin_unsetenv(args, env);
    if (!my_strcmp(args[0], "exit"))
        return builtin_exit(args);
    return -1;
}

int exec_builtin(char **args, char ***env)
{
    int r = handle_group1(args, env);

    if (r != -1)
        return r;
    r = handle_group2(args, env);
    if (r != -1)
        return r;
    return 0;
}
