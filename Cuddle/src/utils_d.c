/*
** EPITECH PROJECT, 2024
** ia
** File description:
** utils_d.c
*/

#include "dataframe.h"

static void compute_flags(char **vals, int nb_rows, flags_t *flags)
{
    int i = 0;

    flags->has_int = 1;
    flags->has_bool = 1;
    flags->has_float = 0;
    flags->has_neg = 0;
    for (i = 0; i < nb_rows; i++) {
        if (!vals[i])
            continue;
        if (!is_int(vals[i]))
            flags->has_int = 0;
        if (!is_bool(vals[i]))
            flags->has_bool = 0;
        if (is_float(vals[i]))
            flags->has_float = 1;
        if (vals[i][0] == '-')
            flags->has_neg = 1;
    }
}

column_type_t detect_column_type(char **vals, int nb_rows)
{
    flags_t flags;

    compute_flags(vals, nb_rows, &flags);
    if (flags.has_bool && nb_rows > 0)
        return (BOOL);
    if (flags.has_int && nb_rows > 0 && !flags.has_float) {
        if (flags.has_neg)
            return (INT);
        return (UINT);
    }
    if (flags.has_float)
        return (FLOAT);
    return (STRING);
}

int find_column_index(dataframe_t *df, const char *column)
{
    int i = 0;

    if (!df || !column)
        return (-1);
    for (i = 0; i < df->nb_columns; i++) {
        if (!strcmp(df->column_names[i], column))
            return (i);
    }
    return (-1);
}

dataframe_t *init_df(void)
{
    dataframe_t *df = malloc(sizeof(*df));

    if (df == NULL)
        return (NULL);
    df->nb_rows = 0;
    df->nb_columns = 0;
    df->column_names = NULL;
    df->column_types = NULL;
    df->data = NULL;
    return (df);
}

void clean_line(char *line)
{
    char *cr = strchr(line, '\r');
    char *nl = strchr(line, '\n');

    if (cr != NULL)
        *cr = '\0';
    if (nl != NULL)
        *nl = '\0';
}

char **split_line(char *line, const char *sep, int *count)
{
    char **res = NULL;
    int c = 0;
    char *token = strtok(line, sep);
    char **tmp;

    while (token) {
        tmp = realloc(res, sizeof(char *) * (c + 1));
        if (tmp == NULL)
            return (NULL);
        res = tmp;
        res[c] = strdup(token);
        c++;
        token = strtok(NULL, sep);
    }
    *count = c;
    return (res);
}
