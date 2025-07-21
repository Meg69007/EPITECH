/*
** EPITECH PROJECT, 2024
** ia
** File description:
** tail.c
*/

#include "dataframe.h"

static dataframe_t *allocate_tail_df(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = malloc(sizeof(*new_df));
    int c = 0;

    if (!new_df)
        return (NULL);
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * new_df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * new_df->nb_columns);
    new_df->data = malloc(sizeof(char **) * new_df->nb_columns);
    for (c = 0; c < new_df->nb_columns; c++) {
        new_df->column_names[c] = strdup(df->column_names[c]);
        new_df->column_types[c] = df->column_types[c];
        new_df->data[c] = NULL;
    }
    return (new_df);
}

dataframe_t *df_tail(dataframe_t *df, int nb_rows)
{
    dataframe_t *tail_df = NULL;
    int start = 0;
    int c = 0;
    int r = 0;

    if (!df || nb_rows < 0)
        return (NULL);
    if (nb_rows > df->nb_rows)
        nb_rows = df->nb_rows;
    start = df->nb_rows - nb_rows;
    tail_df = allocate_tail_df(df, nb_rows);
    if (!tail_df)
        return (NULL);
    for (c = 0; c < tail_df->nb_columns; c++) {
        tail_df->data[c] = malloc(sizeof(char *) * nb_rows);
        for (r = 0; r < nb_rows; r++)
            tail_df->data[c][r] = strdup(df->data[c][start + r]);
    }
    return (tail_df);
}
