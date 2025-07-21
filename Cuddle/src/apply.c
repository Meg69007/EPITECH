/*
** EPITECH PROJECT, 2024
** ia
** File description:
** apply.c
*/

#include "dataframe.h"

static dataframe_t *allocate_dataframe_copy(dataframe_t *df)
{
    dataframe_t *new_df = malloc(sizeof(*new_df));

    if (!new_df)
        return (NULL);
    new_df->nb_rows = df->nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * new_df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * new_df->nb_columns);
    new_df->data = malloc(sizeof(char **) * new_df->nb_columns);
    if (!new_df->column_names || !new_df->column_types || !new_df->data)
        return (NULL);
    return (new_df);
}

static int copy_column_data(dataframe_t *src, dataframe_t *dest, int i)
{
    int row_count = src->nb_rows;
    int r = 0;

    dest->column_names[i] = strdup(src->column_names[i]);
    dest->column_types[i] = src->column_types[i];
    dest->data[i] = malloc(sizeof(char *) * row_count);
    if (!dest->data[i])
        return (1);
    for (r = 0; r < row_count; r++) {
        dest->data[i][r] = strdup(src->data[i][r]);
        if (!dest->data[i][r])
            return (1);
    }
    return (0);
}

static dataframe_t *copy_dataframe(dataframe_t *df)
{
    dataframe_t *new_df = NULL;
    int c = 0;
    int ret = 0;

    new_df = allocate_dataframe_copy(df);
    if (!new_df)
        return (NULL);
    for (c = 0; c < df->nb_columns; c++) {
        ret = copy_column_data(df, new_df, c);
        if (ret != 0)
            return (NULL);
    }
    return (new_df);
}

static void *transform_apply(void *old_val, void *(*apply_func)(void *))
{
    void *new_val = apply_func(old_val);

    free(old_val);
    return (new_val);
}

dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *))
{
    dataframe_t *new_df = NULL;
    int col_idx = 0;
    int r = 0;
    void *old_val;

    if (!df || !column || !apply_func)
        return (NULL);
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return (NULL);
    new_df = copy_dataframe(df);
    if (!new_df)
        return (NULL);
    for (r = 0; r < new_df->nb_rows; r++) {
        old_val = new_df->data[col_idx][r];
        new_df->data[col_idx][r] = transform_apply(old_val, apply_func);
    }
    return (new_df);
}
