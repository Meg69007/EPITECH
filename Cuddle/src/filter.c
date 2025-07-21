/*
** EPITECH PROJECT, 2024
** ia
** File description:
** filter.c
*/

#include "dataframe.h"

static int *collect_valid_rows(dataframe_t *df, const char *column,
    bool (*filter_func)(void *), int *valid_count)
{
    int col_idx = 0;
    int *rows = NULL;
    int r = 0;

    *valid_count = 0;
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return (NULL);
    rows = malloc(sizeof(int) * df->nb_rows);
    for (r = 0; r < df->nb_rows; r++) {
        if (filter_func((void *)df->data[col_idx][r])) {
            rows[*valid_count] = r;
            (*valid_count)++;
        }
    }
    return (rows);
}

static dataframe_t *allocate_filtered_df(dataframe_t *df, int valid_count)
{
    dataframe_t *new_df = NULL;
    int c = 0;

    new_df = malloc(sizeof(*new_df));
    if (!new_df)
        return (NULL);
    new_df->nb_rows = valid_count;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * new_df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * new_df->nb_columns);
    new_df->data = malloc(sizeof(char **) * new_df->nb_columns);
    if (!new_df->column_names || !new_df->column_types || !new_df->data)
        return (NULL);
    for (c = 0; c < df->nb_columns; c++) {
        new_df->column_names[c] = strdup(df->column_names[c]);
        new_df->column_types[c] = df->column_types[c];
        new_df->data[c] = NULL;
    }
    return (new_df);
}

static int copy_filtered_data(dataframe_t *df, dataframe_t *new_df,
    int *rows, int valid_count)
{
    int c = 0;
    int i = 0;

    for (c = 0; c < df->nb_columns; c++) {
        new_df->data[c] = malloc(sizeof(char *) * valid_count);
        if (!new_df->data[c])
            return (1);
        for (i = 0; i < valid_count; i++)
            new_df->data[c][i] = strdup(df->data[c][rows[i]]);
    }
    return (0);
}

dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_func)(void *))
{
    int valid_count = 0;
    int *rows = NULL;
    dataframe_t *new_df = NULL;

    if (!df || !column || !filter_func)
        return (NULL);
    rows = collect_valid_rows(df, column, filter_func, &valid_count);
    if (!rows)
        return (NULL);
    new_df = allocate_filtered_df(df, valid_count);
    if (!new_df) {
        free(rows);
        return (NULL);
    }
    if (copy_filtered_data(df, new_df, rows, valid_count) != 0)
        return (NULL);
    free(rows);
    return (new_df);
}
