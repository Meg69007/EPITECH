/*
** EPITECH PROJECT, 2024
** ia
** File description:
** free.c
*/

#include "dataframe.h"

void df_free(dataframe_t *df)
{
    int c = 0;
    int r = 0;

    if (!df) {
        return;
    }
    for (c = 0; c < df->nb_columns; c++) {
        free(df->column_names[c]);
        for (r = 0; r < df->nb_rows; r++) {
            free(df->data[c][r]);
        }
        free(df->data[c]);
    }
    free(df->column_names);
    free(df->column_types);
    free(df->data);
    free(df);
}
