/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** redirect.c
*/

#include <fcntl.h>
#include <unistd.h>
#include "mysh.h"

int apply_in_redirection(cmd_t *c)
{
    int fd;

    if (c->infile) {
        fd = open(c->infile, O_RDONLY);
        if (fd < 0)
            return -1;
        dup2(fd, 0);
        close(fd);
    }
    return 0;
}

int apply_out_redirection(cmd_t *c)
{
    int fd;
    int flags;

    if (c->outfile) {
        flags = O_WRONLY | O_CREAT;
        if (c->append_out)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
        fd = open(c->outfile, flags, 0664);
        if (fd < 0)
            return -1;
        dup2(fd, 1);
        close(fd);
    }
    return 0;
}

int apply_redirections(cmd_t *c)
{
    if (apply_in_redirection(c) < 0)
        return -1;
    if (apply_out_redirection(c) < 0)
        return -1;
    return 0;
}
