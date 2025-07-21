/*
** EPITECH PROJECT, 2024
** G-AIA-200-LYN-2-1-cuddle-gabriel.megroian
** File description:
** read.c
*/

#include "dataframe.h"

static int allocate_row(dataframe_t *df)
{
    int col = 0;
    int new_row = df->nb_rows + 1;
    char **tmp;

    for (col = 0; col < df->nb_columns; col++) {
        tmp = realloc(df->data[col], sizeof(char *) * new_row);
        if (tmp == NULL)
            return (1);
        df->data[col] = tmp;
    }
    return (0);
}

static int fill_row_from_tokens(dataframe_t *df, char **vals, int token_count)
{
    int col = 0;

    for (col = 0; col < df->nb_columns; col++) {
        if (col < token_count)
            df->data[col][df->nb_rows - 1] = strdup(vals[col]);
        else
            df->data[col][df->nb_rows - 1] = strdup("");
    }
    return (0);
}

static void free_tokens(char **vals, int token_count)
{
    int i = 0;

    for (i = 0; i < token_count; i++)
        free(vals[i]);
    free(vals);
}

static int fill_data_row(dataframe_t *df, const char *sep, char *line)
{
    int token_count = 0;
    char **vals = NULL;

    clean_line(line);
    vals = split_line(line, sep, &token_count);
    if (vals == NULL)
        return (1);
    if (allocate_row(df) != 0) {
        free_tokens(vals, token_count);
        return (1);
    }
    df->nb_rows++;
    if (fill_row_from_tokens(df, vals, token_count) != 0) {
        free_tokens(vals, token_count);
        return (1);
    }
    free_tokens(vals, token_count);
    return (0);
}

static int init_header_from_tokens(dataframe_t *df, char **cols, int count)
{
    int i = 0;

    df->nb_columns = count;
    df->column_names = malloc(sizeof(char *) * count);
    df->data = malloc(sizeof(char **) * count);
    if (df->column_names == NULL || df->data == NULL)
        return (1);
    for (i = 0; i < count; i++) {
        df->column_names[i] = strdup(cols[i]);
        df->data[i] = NULL;
        free(cols[i]);
    }
    free(cols);
    return (0);
}

static int read_header(FILE *fp, dataframe_t *df, const char *sep)
{
    char *line_buf = malloc(LINE_SIZE);
    int count = 0;
    char **cols = NULL;

    if (line_buf == NULL)
        return (1);
    if (fgets(line_buf, LINE_SIZE, fp) == NULL) {
        free(line_buf);
        return (1);
    }
    clean_line(line_buf);
    cols = split_line(line_buf, sep, &count);
    free(line_buf);
    if (cols == NULL || count == 0) {
        free(cols);
        return (1);
    }
    return (init_header_from_tokens(df, cols, count));
}

static int read_data(FILE *fp, dataframe_t *df, const char *sep)
{
    char *line = malloc(LINE_SIZE);
    size_t len = LINE_SIZE;
    int status = 0;

    if (line == NULL)
        return (1);
    while (getline(&line, &len, fp) != -1) {
        clean_line(line);
        status = fill_data_row(df, sep, line);
        if (status != 0) {
            free(line);
            return (1);
        }
    }
    free(line);
    return (0);
}

static int finalize_df(dataframe_t *df)
{
    int i = 0;

    df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    if (df->column_types == NULL)
        return (1);
    for (i = 0; i < df->nb_columns; i++)
        df->column_types[i] = detect_column_type(df->data[i], df->nb_rows);
    return (0);
}

static dataframe_t *process_csv(FILE *fp, const char *separator)
{
    dataframe_t *df = init_df();

    if (df == NULL)
        return (NULL);
    if (read_header(fp, df, separator) != 0) {
        df_free(df);
        return (NULL);
    }
    if (read_data(fp, df, separator) != 0) {
        df_free(df);
        return (NULL);
    }
    if (finalize_df(df) != 0) {
        df_free(df);
        return (NULL);
    }
    return (df);
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *fp = NULL;
    dataframe_t *df = NULL;

    if (separator == NULL)
        separator = ",";
    fp = fopen(filename, "r");
    if (fp == NULL)
        return (NULL);
    df = process_csv(fp, separator);
    fclose(fp);
    return (df);
}
