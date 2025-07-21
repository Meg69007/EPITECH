/*
** EPITECH PROJECT, 2024
** ia
** File description:
** group_fill.c
*/

#include "dataframe.h"

int count_grouped_cols(const char **to_agg)
{
    int col_count = 1;

    while (to_agg[col_count - 1]) {
        col_count++;
    }
    return (col_count);
}

static dataframe_t *init_grouped_df(int col_count, int unique_count)
{
    dataframe_t *new_df;

    new_df = malloc(sizeof(*new_df));
    if (new_df == NULL)
        return (NULL);
    new_df->nb_rows = unique_count;
    new_df->nb_columns = col_count;
    new_df->column_names = malloc(sizeof(char *) * col_count);
    new_df->column_types = malloc(sizeof(column_type_t) * col_count);
    new_df->data = malloc(sizeof(char **) * col_count);
    if (new_df->column_names == NULL ||
        new_df->column_types == NULL ||
        new_df->data == NULL)
        return (NULL);
    return (new_df);
}

static void init_grouped_df_key(dataframe_t *new_df,
    const char *group_by, int unique_count)
{
    new_df->column_names[0] = strdup(group_by);
    new_df->column_types[0] = STRING;
    new_df->data[0] = malloc(sizeof(char *) * unique_count);
}

static void fill_grouped_df_columns(dataframe_t *new_df,
    dataframe_t *df, const char **to_agg, int unique_count)
{
    int i = 0;
    int idx = 0;
    int col_count = count_grouped_cols(to_agg);

    for (i = 1; i < col_count; i++) {
        idx = find_column_index(df, to_agg[i - 1]);
        new_df->column_names[i] = strdup(to_agg[i - 1]);
        if (idx >= 0)
            new_df->column_types[i] = df->column_types[idx];
        else
            new_df->column_types[i] = UNDEFINED;
        new_df->data[i] = malloc(sizeof(char *) * unique_count);
    }
}

static dataframe_t *allocate_groupe_df(dataframe_t *df, const char *group_by,
    const char **to_agg, int unique_count)
{
    int col_count = count_grouped_cols(to_agg);
    dataframe_t *new_df = init_grouped_df(col_count, unique_count);

    if (new_df == NULL)
        return (NULL);
    init_grouped_df_key(new_df, group_by, unique_count);
    fill_grouped_df_columns(new_df, df, to_agg, unique_count);
    return (new_df);
}

void fill_group_key(dataframe_t *new_df, char **unique_vals, int unique_count)
{
    int i = 0;

    for (i = 0; i < unique_count; i++) {
        new_df->data[0][i] = strdup(unique_vals[i]);
    }
}

group_ctx_t *setup_group_ctx(dataframe_t *df, const char *group_by,
    void *(*agg_func)(void **, int))
{
    group_ctx_t *ctx = malloc(sizeof(group_ctx_t));

    if (ctx == NULL)
        return (NULL);
    ctx->df = df;
    ctx->agg_func = agg_func;
    ctx->by_idx = find_column_index(df, group_by);
    ctx->unique_vals = NULL;
    ctx->unique_count = 0;
    ctx->new_df = NULL;
    return (ctx);
}

dataframe_t *create_grouped_df_from_ctx(dataframe_t *df,
    const char *group_by, const char **to_aggregate, group_ctx_t *ctx)
{
    ctx->unique_count = unique_str_count(df->data[ctx->by_idx], df->nb_rows);
    ctx->unique_vals = unique_strs(df->data[ctx->by_idx], df->nb_rows,
        &ctx->unique_count);
        if (ctx->unique_vals == NULL)
        return (NULL);
    return (allocate_groupe_df(df, group_by, to_aggregate, ctx->unique_count));
}

int finalize_grouped_df(group_ctx_t *ctx, const char **to_aggregate)
{
    fill_group_key(ctx->new_df, ctx->unique_vals, ctx->unique_count);
    return (fill_all_aggregations(ctx, to_aggregate));
}
