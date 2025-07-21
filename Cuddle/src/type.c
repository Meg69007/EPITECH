/*
** EPITECH PROJECT, 2024
** ia
** File description:
** type.c
*/

#include "dataframe.h"

static char *convert_int_value(const char *old, column_type_t dow)
{
    char buf[64];
    long long val = 0;

    if (!is_int(old) && !is_float(old))
        return (NULL);
    val = my_atoll(old);
    if (val < 0 && dow == UINT)
        return (NULL);
    sprintf(buf, "%lld", val);
    return (strdup(buf));
}

static char *convert_float_value(const char *old)
{
    char buf[64];
    double val = 0;

    if (!is_int(old) && !is_float(old))
        return (NULL);
    val = my_atof(old);
    sprintf(buf, "%.0f", val);
    return (strdup(buf));
}

static char *convert_bool_value(const char *old)
{
    int cond = (my_atof(old) != 0);

    return (strdup(cond ? "true" : "false"));
}

static char *select_conversion(const char *old, column_type_t dow)
{
    switch (dow) {
        case INT:
        case UINT:
            return (convert_int_value(old, dow));
        case FLOAT:
            return (convert_float_value(old));
        case BOOL:
            return (convert_bool_value(old));
        default:
            return (NULL);
    }
}

static int convert_single_value(dataframe_t *new, int idx, int r,
    column_type_t dow)
{
    char *old = new->data[idx][r];
    char *new_val = select_conversion(old, dow);

    if (!new_val)
        return (1);
    free(old);
    new->data[idx][r] = new_val;
    return (0);
}

static int convert_column_values(dataframe_t *new, int idx, column_type_t dow)
{
    int r = 0;
    int ret = 0;

    for (r = 0; r < new->nb_rows; r++) {
        ret = convert_single_value(new, idx, r, dow);
        if (ret)
            return (1);
    }
    return (0);
}

dataframe_t *df_to_type(dataframe_t *df, const char *column, column_type_t dow)
{
    dataframe_t *new = NULL;
    int idx = 0;
    int err = 0;

    if (!df || !column)
        return (NULL);
    idx = find_column_index(df, column);
    if (idx < 0)
        return (NULL);
    new = df_head(df, df->nb_rows);
    new->column_types[idx] = dow;
    err = convert_column_values(new, idx, dow);
    if (err) {
        df_free(new);
        return (NULL);
    }
    return (new);
}
