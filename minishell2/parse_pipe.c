/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** parse_pipe.c
*/

#include "mysh.h"

cmd_t *alloc_cmd(void)
{
    cmd_t *c = malloc(sizeof(cmd_t));

    if (c == NULL)
        return NULL;
    c->argv = NULL;
    c->infile = NULL;
    c->outfile = NULL;
    c->append_out = 0;
    c->next = NULL;
    return c;
}

static int handle_redirection_token(char **arr, int i, cmd_t *c)
{
    if (my_strcmp(arr[i], ">") == 0 || my_strcmp(arr[i], ">>") == 0) {
        c->outfile = (arr[i + 1] != NULL) ? arr[i + 1] : NULL;
        c->append_out = (my_strcmp(arr[i], ">>") == 0) ? 1 : 0;
        return 2;
    } else if (my_strcmp(arr[i], "<") == 0) {
        c->infile = (arr[i + 1] != NULL) ? arr[i + 1] : NULL;
        return 2;
    }
    return 0;
}

void parse_redirs(char **arr, cmd_t *c)
{
    int i = 0;
    int j = 0;
    int skip = 0;

    while (arr[i] != NULL) {
        skip = handle_redirection_token(arr, i, c);
        if (skip > 0)
            i = i + skip;
        else {
            arr[j] = arr[i];
            j = j + 1;
            i = i + 1;
        }
    }
    arr[j] = NULL;
    c->argv = arr;
}
