/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** exec.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mysh.h"

int exec_command(char **args, char **env)
{
    pid_t pid = fork();

    if (pid < 0) {
        my_puterr("fork failed.\n");
        return 1;
    }
    if (pid == 0)
        exec_child(args, env);
    return handle_wait(pid);
}

void exec_child(char **args, char **env)
{
    char *cmd_path = find_in_path(args[0], env);

    if (!cmd_path) {
        my_puterr(args[0]);
        my_puterr(": Command not found.\n");
        exit(1);
    }
    execve(cmd_path, args, env);
    my_puterr("execve: failed.\n");
    free(cmd_path);
    exit(1);
}

static int report_signal(int sig)
{
    if (sig == 8)
        my_puterr("Floating exception (core dumped)\n");
    else if (sig == 11)
        my_puterr("Segmentation fault (core dumped)\n");
    return 128 + sig;
}

int handle_wait(pid_t pid)
{
    int status = 0;
    int sig;

    if (waitpid(pid, &status, 0) < 0) {
        my_puterr("waitpid failed.\n");
        return 1;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        return report_signal(sig);
    }
    return 0;
}

char *check_direct_path(const char *cmd)
{
    if (access(cmd, X_OK) == 0)
        return my_strdup(cmd);
    return NULL;
}

char *find_in_path(const char *cmd, char **env)
{
    char *path = my_getenv(env, "PATH");
    char *copy = NULL;
    char *res = NULL;

    if (my_strchr(cmd, '/'))
        return check_direct_path(cmd);
    if (!path)
        return NULL;
    copy = my_strdup(path);
    if (!copy)
        return NULL;
    res = search_in_path(copy, cmd);
    free(copy);
    return res;
}
