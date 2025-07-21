/*
** EPITECH PROJECT, 2024
** ia
** File description:
** value.c
*/

#include "dataframe.h"

static int is_value_in_list(void **list, int count, const char *value)
{
    int j = 0;

    for (j = 0; j < count; j++) {
        if (strcmp(list[j], value) == 0)
            return (1);
    }
    return (0);
}

void *df_get_value(dataframe_t *df, int row, const char *column)
{
    int col_idx = 0;
    char *raw = NULL;
    int *val_int = NULL;

    if (df == NULL || row < 0 || row >= df->nb_rows)
        return NULL;
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return NULL;
    if (df->column_types[col_idx] == INT) {
        raw = df->data[col_idx][row];
        val_int = malloc(sizeof(int));
        if (val_int == NULL)
            return NULL;
        *val_int = atoi(raw);
        return val_int;
    }
    return df->data[col_idx][row];
}

static void *convert_token_value(const char *str, column_type_t type)
{
    int *val_int = NULL;

    if (type == INT) {
        val_int = malloc(sizeof(int));
        if (val_int == NULL)
            return (NULL);
        *val_int = atoi(str);
        return (val_int);
    }
    return (void *)str;
}

static int fill_values_array(dataframe_t *df, int col_idx, void **res)
{
    int i = 0;
    void *converted = NULL;

    for (i = 0; i < df->nb_rows; i++) {
        converted = convert_token_value(df->data[col_idx][i],
            df->column_types[col_idx]);
        if (converted == NULL && df->column_types[col_idx] == INT)
            return (1);
        res[i] = converted;
    }
    res[df->nb_rows] = NULL;
    return (0);
}

void **df_get_values(dataframe_t *df, const char *column)
{
    int col_idx = 0;
    void **res = NULL;

    if (df == NULL || column == NULL)
        return (NULL);
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return (NULL);
    res = malloc(sizeof(void *) * (df->nb_rows + 1));
    if (res == NULL)
        return (NULL);
    if (fill_values_array(df, col_idx, res) != 0) {
        free(res);
        return (NULL);
    }
    return res;
}

static int append_unique_value(void ***pres, int *pcount, char *value)
{
    void **tmp = realloc(*pres, sizeof(void *) * ((*pcount) + 1));

    if (tmp == NULL)
        return (1);
    *pres = tmp;
    (*pres)[*pcount] = value;
    (*pcount)++;
    return (0);
}

static void **collect_unique_strings(char **col_data, int nb_rows)
{
    void **res = NULL;
    int count = 0;
    int i = 0;
    void **tmp = NULL;

    for (i = 0; i < nb_rows; i++) {
        if (is_value_in_list(res, count, col_data[i]))
            continue;
        if (append_unique_value(&res, &count, col_data[i]) != 0)
            return (res);
    }
    tmp = realloc(res, sizeof(void *) * (count + 1));
    if (tmp != NULL)
        res = tmp;
    res[count] = NULL;
    return (res);
}

void **df_get_unique_values(dataframe_t *df, const char *column)
{
    int col_idx = 0;
    void **res = NULL;

    if (df == NULL || column == NULL)
        return (NULL);
    col_idx = find_column_index(df, column);
    if (col_idx < 0)
        return (NULL);
    res = collect_unique_strings(df->data[col_idx], df->nb_rows);
    return (res);
}
