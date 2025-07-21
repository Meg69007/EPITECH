/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** shell_loop.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysh.h"

static int process_command(char *line, char ***env_cpy)
{
    pipeline_t *pipelines = parse_line(line);
    int ret = 0;
    pipeline_t *tmp = pipelines;
    pipeline_t *next;

    while (tmp) {
        ret = exec_pipeline(tmp->cmds, env_cpy);
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    return ret;
}

void shell_loop(char **env_cpy)
{
    char *line = NULL;
    size_t len = 0;
    int r;
    ssize_t nread;

    while (1) {
        write(1, "$> ", 3);
        nread = getline(&line, &len, stdin);
        if (nread < 0)
            break;
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';
        r = process_command(line, &env_cpy);
        if (r == EXIT_SHELL)
            break;
    }
    free(line);
}
