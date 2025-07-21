/*
** EPITECH PROJECT, 2024
** ia
** File description:
** sort.c
*/

#include "dataframe.h"

static void swap_rows(dataframe_t *df, int r1, int r2)
{
    int c = 0;
    char *tmp = NULL;

    for (c = 0; c < df->nb_columns; c++) {
        tmp = df->data[c][r1];
        df->data[c][r1] = df->data[c][r2];
        df->data[c][r2] = tmp;
    }
}

static void process_comparison(sort_context_t *ctx, int i, int j)
{
    if (ctx->sort_func(ctx->df->data[ctx->col_idx][i],
    ctx->df->data[ctx->col_idx][j]))
        swap_rows(ctx->df, i, j);
}

static void sort_data(dataframe_t *df, int col_idx,
    bool (*sort_func)(void *, void *))
{
    int i = 0;
    int j = 0;
    sort_context_t ctx;

    ctx.df = df;
    ctx.col_idx = col_idx;
    ctx.sort_func = sort_func;
    for (i = 0; i < df->nb_rows - 1; i++) {
        for (j = i + 1; j < df->nb_rows; j++) {
            process_comparison(&ctx, i, j);
        }
    }
}

dataframe_t *df_sort(dataframe_t *df, const char *column,
    bool (*sort_func)(void *, void *))
{
    int col_idx = 0;
    dataframe_t *new_df = NULL;

    if (!df || !column || !sort_func)
        return (NULL);
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return (NULL);
    new_df = df_head(df, df->nb_rows);
    if (!new_df)
        return (NULL);
    sort_data(new_df, col_idx, sort_func);
    return (new_df);
}
