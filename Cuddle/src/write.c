/*
** EPITECH PROJECT, 2024
** ia
** File description:
** write.c
*/

#include "dataframe.h"

static void write_csv_header(FILE *fp, dataframe_t *df)
{
    int i;

    for (i = 0; i < df->nb_columns; i++) {
        fprintf(fp, "%s%s", df->column_names[i],
            (i < df->nb_columns - 1) ? "," : "");
    }
    fprintf(fp, "\n");
}

static void write_csv_rows(FILE *fp, dataframe_t *df)
{
    int i;
    int r;

    for (r = 0; r < df->nb_rows; r++) {
        for (i = 0; i < df->nb_columns; i++) {
            fprintf(fp, "%s%s", df->data[i][r],
                (i < df->nb_columns - 1) ? "," : "");
        }
        fprintf(fp, "\n");
    }
}

int df_write_csv(dataframe_t *df, const char *filename)
{
    FILE *fp;

    if (!df || !filename)
        return (1);
    fp = fopen(filename, "w");
    if (!fp)
        return (1);
    write_csv_header(fp, df);
    write_csv_rows(fp, df);
    fclose(fp);
    return (0);
}
