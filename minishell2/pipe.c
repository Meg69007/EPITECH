/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** pipe.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "mysh.h"

static void child_proc(cmd_t *c, int in, int out, char ***env)
{
    if (in != 0) {
        dup2(in, 0);
        close(in);
    }
    if (out != 1) {
        dup2(out, 1);
        close(out);
    }
    if (apply_redirections(c) < 0)
        exit(1);
    if (is_builtin_command(c->argv[0])) {
        exec_builtin(c->argv, env);
        exit(0);
    }
    execvp(c->argv[0], c->argv);
    exit(1);
}

static int wait_all(void)
{
    int status;
    int ret;
    pid_t p;

    ret = 0;
    while (1) {
        p = wait(&status);
        if (p < 0)
            break;
        if (WIFEXITED(status))
            ret = WEXITSTATUS(status);
        else
            ret = 1;
    }
    return ret;
}

static int create_pipe_and_fork(cmd_t *cur, int in, int fd[2], char ***env)
{
    pid_t pid;

    if (cur->next) {
        if (pipe(fd) < 0)
            return -1;
    }
    pid = fork();
    if (pid < 0)
        return -1;
    if (pid == 0) {
        if (cur->next)
            child_proc(cur, in, fd[1], env);
        else
            child_proc(cur, in, 1, env);
    }
    return pid;
}

static int handle_parent_after_fork(cmd_t *cur, int in, int fd[2], int *new_in)
{
    if (in != 0)
        close(in);
    if (cur->next) {
        close(fd[1]);
        *new_in = fd[0];
    } else
        *new_in = 0;
    return 0;
}

static int process_pipe(cmd_t *cur, int in, int *new_in, char ***env)
{
    int fd[2] = {0, 0};

    if (create_pipe_and_fork(cur, in, fd, env) < 0)
        return -1;
    return handle_parent_after_fork(cur, in, fd, new_in);
}

static int exec_pipeline_loop(cmd_t *c, char ***env)
{
    cmd_t *cur;
    int in;
    int ret;

    in = 0;
    cur = c;
    while (cur) {
        if (process_pipe(cur, in, &in, env) < 0)
            return 1;
        cur = cur->next;
    }
    ret = wait_all();
    return ret;
}

int exec_pipeline(cmd_t *c, char ***env)
{
    if (!c)
        return 0;
    if (!c->next && is_builtin_command(c->argv[0])) {
        if (apply_redirections(c) < 0)
            return 1;
        return exec_builtin(c->argv, env);
    }
    return exec_pipeline_loop(c, env);
}
