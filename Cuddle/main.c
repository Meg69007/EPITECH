/*
** EPITECH PROJECT, 2025
** LIBCUDDLE
** File description:
** main_read_write.c
*/

#include "include/dataframe.h"
#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    dataframe_t *df = df_read_csv("output.csv", NULL);
    // if (df == NULL)
    // {
    //     fprintf(stderr, "Error reading data.csv\n");
    //     return (84);
    // }
    // printf("=== Original CSV ===\n");
    df_describe(df);
    // print_shape(df);

    //if (df_write_csv(df, "out.csv") != 0)
    //{
    //    fprintf(stderr, "Error writing out.csv\n");
    //    df_free(df);
    //    return (84);
    //}
   // printf("CSV written to out.csv\n");

    // dataframe_t *df2 = df_read_csv("out.csv", NULL);
    // if (df2 == NULL)
    // {
        // fprintf(stderr, "Error reading out.csv\n");
        // df_free(df);
        // return (84);
    // }
    // printf("=== Re-read CSV ===\n");
    // df_info(df2);
    // print_shape(df2);

    // if (df->nb_rows != df2->nb_rows || df->nb_columns != df2->nb_columns)
    // {
        // fprintf(stderr, "Mismatch between original and re-read CSV\n");
        // df_free(df);
        // df_free(df2);
        // return (84);
    // }
    df_free(df);
    // df_free(df2);
    return (0);
}
