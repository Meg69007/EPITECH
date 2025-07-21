/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** parse_line_utils.c
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

char **split_tokens(char *s, const char *del)
{
    char **arr;
    int i;
    char *tok;

    arr = malloc(sizeof(char *) * 256);
    if (arr == NULL)
        return NULL;
    i = 0;
    tok = strtok(s, del);
    while (tok != NULL && i < 255) {
        arr[i] = tok;
        i = i + 1;
        tok = strtok(NULL, del);
    }
    arr[i] = NULL;
    return arr;
}

char **split_semicolons(char *line)
{
    char **arr;
    int i;
    char *tok;

    arr = malloc(sizeof(char *) * 128);
    if (arr == NULL)
        return NULL;
    i = 0;
    tok = strtok(line, ";");
    while (tok != NULL && i < 127) {
        arr[i] = tok;
        i = i + 1;
        tok = strtok(NULL, ";");
    }
    arr[i] = NULL;
    return arr;
}

char **split_or(char *blk)
{
    char **arr;
    int i;
    char *tok;

    arr = malloc(sizeof(char *) * 128);
    if (arr == NULL)
        return NULL;
    i = 0;
    tok = strtok(blk, "||");
    while (tok != NULL && i < 127) {
        arr[i] = tok;
        i = i + 1;
        tok = strtok(NULL, "||");
    }
    arr[i] = NULL;
    return arr;
}

pipeline_t *build_pipeline_from_chain(chain_t *cchain)
{
    pipeline_t *first = NULL;
    pipeline_t *last = NULL;
    int res = 0;
    chain_t *tmp = NULL;

    while (cchain != NULL) {
        res = add_node_if(cchain, &first, &last);
        if (res < 0)
            break;
        tmp = cchain;
        cchain = cchain->next;
        free(tmp);
    }
    return first;
}
