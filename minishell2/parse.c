/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-gabriel.megroian
** File description:
** parse.c
*/

#include "mysh.h"

pipeline_t *process_block(char *block)
{
    chain_t *chain = parse_or_chain(block);

    return build_pipeline_from_chain(chain);
}

void add_pip(pipeline_t **first, pipeline_t **last, pipeline_t *node)
{
    if (*first == NULL) {
        *first = node;
        *last = node;
        while ((*last)->next != NULL) {
            *last = (*last)->next;
        }
    } else {
        (*last)->next = node;
        while ((*last)->next != NULL) {
            *last = (*last)->next;
        }
    }
}

pipeline_t *assemble_pipelines(char **blocks)
{
    pipeline_t *first_pipeline = NULL;
    pipeline_t *last_pipeline = NULL;
    pipeline_t *node = NULL;
    int i = 0;

    while (blocks[i] != NULL) {
        node = process_block(blocks[i]);
        if (node != NULL) {
            add_pip(&first_pipeline, &last_pipeline, node);
        }
        i = i + 1;
    }
    return first_pipeline;
}

pipeline_t *create_pipeline_node(chain_t *cchain)
{
    pipeline_t *node = malloc(sizeof(pipeline_t));

    if (node == NULL)
        return NULL;
    node->cmds = cchain->cmds;
    node->next = NULL;
    return node;
}
