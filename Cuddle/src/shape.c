/*
** EPITECH PROJECT, 2024
** ia
** File description:
** shape.c
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *df)
{
    dataframe_shape_t s;

    s.nb_rows = 0;
    s.nb_columns = 0;
    if (!df)
        return (s);
    s.nb_rows = df->nb_rows;
    s.nb_columns = df->nb_columns;
    return (s);
}
