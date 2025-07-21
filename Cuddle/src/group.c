/*
** EPITECH PROJECT, 2024
** ia
** File description:
** group.c
*/

#include "dataframe.h"

static int append_value_if_match(group_ctx_t *ctx, int i, agg_params_t p,
    agg_accum_t *accum)
{
    char *current = NULL;
    void **tmp = NULL;

    current = ctx->df->data[ctx->by_idx][i];
    if (strcmp(current, ctx->unique_vals[p.row]) != 0)
        return (0);
    tmp = realloc(accum->local_vals, sizeof(void *) * (accum->count + 1));
    if (tmp == NULL)
        return (1);
    accum->local_vals = tmp;
    accum->local_vals[accum->count] = ctx->df->data[p.real_idx][i];
    accum->count++;
    return (0);
}

static int collect_aggregation_values(group_ctx_t *ctx, agg_params_t *params,
    void ***vals, int *val_count)
{
    int i = 0;
    int ret = 0;
    agg_params_t p = *params;
    agg_accum_t accum;

    accum.local_vals = NULL;
    accum.count = 0;
    for (i = 0; i < ctx->df->nb_rows; i++) {
        ret = append_value_if_match(ctx, i, p, &accum);
        if (ret != 0)
            return (1);
    }
    *vals = accum.local_vals;
    *val_count = accum.count;
    return (0);
}

static int process_aggregation_result(group_ctx_t *ctx, agg_params_t *params,
    void **vals, int val_count)
{
    agg_params_t p = *params;
    void *res = ctx->agg_func(vals, val_count);
    char buf[64];

    sprintf(buf, "%lld", *((long long *)res));
    ctx->new_df->data[p.real_idx][p.row] = strdup(buf);
    free(res);
    return (0);
}

int aggregate_for_value(group_ctx_t *ctx, agg_params_t *params)
{
    void **vals = NULL;
    int val_count = 0;
    int ret = 0;

    ret = collect_aggregation_values(ctx, params, &vals, &val_count);
    if (ret != 0) {
        free(vals);
        return (1);
    }
    ret = process_aggregation_result(ctx, params, vals, val_count);
    free(vals);
    return (ret);
}

static int aggregate_one_column(group_ctx_t *ctx, int real_idx)
{
    int row = 0;
    agg_params_t params;

    for (row = 0; row < ctx->unique_count; row++) {
        params.real_idx = real_idx;
        params.row = row;
        if (aggregate_for_value(ctx, &params) != 0)
            return (1);
    }
    return (0);
}

int fill_all_aggregations(group_ctx_t *ctx, const char **to_agg)
{
    int col_count = count_grouped_cols(to_agg);
    int c = 1;
    int real_idx;

    while (c < col_count) {
        real_idx = find_column_index(ctx->df, to_agg[c - 1]);
        if (aggregate_one_column(ctx, real_idx) != 0)
            return (1);
        c++;
    }
    return (0);
}

static void cleanup_ctx(group_ctx_t *ctx)
{
    int i = 0;

    for (i = 0; i < ctx->unique_count; i++)
        free(ctx->unique_vals[i]);
    free(ctx->unique_vals);
    free(ctx);
}

static group_ctx_t *groupby_setup(dataframe_t *df, const char *group_by,
    const char **to_aggregate, void *(*agg_func)(void **, int))
{
    group_ctx_t *ctx = setup_group_ctx(df, group_by, agg_func);

    if (!ctx)
        return (NULL);
    ctx->new_df = create_grouped_df_from_ctx(df, group_by, to_aggregate, ctx);
    if (!ctx->new_df) {
        cleanup_ctx(ctx);
        return (NULL);
    }
    return (ctx);
}

static dataframe_t *groupby_finalize(group_ctx_t *ctx,
    const char **to_aggregate)
{
    fill_group_key(ctx->new_df, ctx->unique_vals, ctx->unique_count);
    if (finalize_grouped_df(ctx, to_aggregate) != 0)
        return (NULL);
    return (ctx->new_df);
}

dataframe_t *df_groupby(dataframe_t *df, const char *group_by,
    const char **to_aggregate, void *(*agg_func)(void **, int))
{
    group_ctx_t *ctx = NULL;
    dataframe_t *new_df = NULL;

    if (!df || !group_by || !to_aggregate || !agg_func)
        return (NULL);
    ctx = groupby_setup(df, group_by, to_aggregate, agg_func);
    if (!ctx)
        return (NULL);
    new_df = groupby_finalize(ctx, to_aggregate);
    if (!new_df) {
        df_free(ctx->new_df);
        cleanup_ctx(ctx);
        return (NULL);
    }
    cleanup_ctx(ctx);
    return (new_df);
}
