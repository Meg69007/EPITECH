/*
** EPITECH PROJECT, 2025
** LIBCUDDLE
** File description:
** head
*/

#include "dataframe.h"

static dataframe_t *allocate_new_df(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = malloc(sizeof(*new_df));
    int i = 0;

    if (!new_df)
        return (NULL);
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    new_df->data = malloc(sizeof(char **) * df->nb_columns);
    for (i = 0; i < df->nb_columns; i++) {
        new_df->column_names[i] = strdup(df->column_names[i]);
        new_df->column_types[i] = df->column_types[i];
        new_df->data[i] = malloc(sizeof(char *) * nb_rows);
    }
    return (new_df);
}

static void copy_rows(dataframe_t *src, dataframe_t *dst, int nb_rows)
{
    int i = 0;
    int r = 0;

    for (i = 0; i < dst->nb_columns; i++) {
        for (r = 0; r < nb_rows; r++) {
            dst->data[i][r] = strdup(src->data[i][r]);
        }
    }
}

dataframe_t *df_head(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = NULL;

    if (!df || nb_rows < 0)
        return (NULL);
    if (nb_rows > df->nb_rows)
        nb_rows = df->nb_rows;
    new_df = allocate_new_df(df, nb_rows);
    if (!new_df)
        return (NULL);
    copy_rows(df, new_df, nb_rows);
    return (new_df);
}
