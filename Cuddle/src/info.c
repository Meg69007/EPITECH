/*
** EPITECH PROJECT, 2024
** ia
** File description:
** info.c
*/

#include "dataframe.h"

static void print_column_info(dataframe_t *df, int i)
{
    printf("- %s: ", df->column_names[i]);
    switch (df->column_types[i]) {
        case BOOL:
            printf("bool\n");
            break;
        case INT:
            printf("int\n");
            break;
        case UINT:
            printf("unsigned int\n");
            break;
        case FLOAT:
            printf("float\n");
            break;
        default:
            printf("string\n");
            break;
    }
}

void df_info(dataframe_t *df)
{
    int i = 0;

    if (!df)
        return;
    printf("%d columns:\n", df->nb_columns);
    for (i = 0; i < df->nb_columns; i++) {
        print_column_info(df, i);
    }
}
