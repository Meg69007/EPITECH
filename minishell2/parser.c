/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** parser.c
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

static cmd_t *parse_one_cmd_internal(char **arr)
{
    cmd_t *c = alloc_cmd();

    if (c == NULL) {
        free(arr);
        return NULL;
    }
    parse_redirs(arr, c);
    if (c->argv == NULL || c->argv[0] == NULL) {
        free(c);
        return NULL;
    }
    return c;
}

static cmd_t *parse_one_cmd(char *seg)
{
    char **arr;

    if (seg == NULL || seg[0] == '\0')
        return NULL;
    arr = split_tokens(seg, " \t");
    if (arr == NULL)
        return NULL;
    return parse_one_cmd_internal(arr);
}

static void append_cmd_node(cmd_t **tail, cmd_t *node)
{
    (*tail)->next = node;
    *tail = node;
}

static cmd_t *build_pipeline_from_tokens(char **pipe_segs)
{
    cmd_t dummy;
    cmd_t *tail;
    cmd_t *cur;
    int i;

    dummy.next = NULL;
    tail = &dummy;
    i = 0;
    while (pipe_segs[i] != NULL) {
        cur = parse_one_cmd(pipe_segs[i]);
        if (cur != NULL)
            append_cmd_node(&tail, cur);
        i = i + 1;
    }
    return dummy.next;
}

static cmd_t *parse_pipeline(char *block)
{
    char **pipe_segs;
    cmd_t *result;

    if (block == NULL || block[0] == '\0')
        return NULL;
    pipe_segs = split_tokens(block, "|");
    if (pipe_segs == NULL)
        return NULL;
    result = build_pipeline_from_tokens(pipe_segs);
    free(pipe_segs);
    return result;
}

static chain_t *create_chain_from_part(char *part, int is_or)
{
    chain_t *ch = malloc(sizeof(chain_t));

    if (ch == NULL)
        return NULL;
    ch->cmds = parse_pipeline(part);
    ch->is_or = is_or;
    ch->next = NULL;
    return ch;
}

static chain_t *build_chain_from_parts(char **parts)
{
    chain_t *start = NULL;
    chain_t *prev = NULL;
    chain_t *ch = NULL;
    int i = 0;

    while (parts[i] != NULL) {
        ch = create_chain_from_part(parts[i], (i > 0) ? 1 : 0);
        if (ch == NULL)
            break;
        if (start == NULL)
            start = ch;
        else
            prev->next = ch;
        prev = ch;
        i = i + 1;
    }
    return start;
}

chain_t *parse_or_chain(char *blk)
{
    char **parts = NULL;
    chain_t *start = NULL;

    if (blk == NULL)
        return NULL;
    parts = split_or(blk);
    if (parts == NULL)
        return NULL;
    start = build_chain_from_parts(parts);
    free(parts);
    return start;
}

int add_node_if(chain_t *cchain, pipeline_t **first, pipeline_t **last)
{
    pipeline_t *node;

    if (cchain->cmds == NULL)
        return 0;
    node = create_pipeline_node(cchain);
    if (node == NULL)
        return -1;
    if (*first == NULL)
        *first = node;
    else
        (*last)->next = node;
    *last = node;
    return 1;
}

pipeline_t *parse_line(char *line)
{
    char **blocks = NULL;
    pipeline_t *result = NULL;

    if (line == NULL) {
        return NULL;
    }
    blocks = split_semicolons(line);
    if (blocks == NULL) {
        return NULL;
    }
    result = assemble_pipelines(blocks);
    free(blocks);
    return result;
}
