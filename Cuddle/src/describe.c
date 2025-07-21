/*
** EPITECH PROJECT, 2024
** ia
** File description:
** describe.c
*/

#include "dataframe.h"

static void compute_basic_stats(dataframe_t *df, int c, column_stats_t *stats)
{
    int r = 0;
    double val = 0;

    stats->count = df->nb_rows;
    stats->sum = 0;
    stats->min = 0;
    stats->max = 0;
    for (r = 0; r < stats->count; r++) {
        val = my_atof(df->data[c][r]);
        if (r == 0) {
            stats->min = val;
            stats->max = val;
        }
        if (val < stats->min)
            stats->min = val;
        if (val > stats->max)
            stats->max = val;
        stats->sum += val;
    }
    stats->mean = stats->sum / stats->count;
}

static double compute_variance(dataframe_t *df, int c, double mean)
{
    int count = df->nb_rows;
    int r = 0;
    double var = 0;
    double val = 0;

    for (r = 0; r < count; r++) {
        val = my_atof(df->data[c][r]) - mean;
        var += val * val;
    }
    return (var / count);
}

static column_stats_t compute_column_stats(dataframe_t *df, int c)
{
    column_stats_t stats;

    compute_basic_stats(df, c, &stats);
    stats.var = compute_variance(df, c, stats.mean);
    return (stats);
}

static void print_column_stats(dataframe_t *df, int c, column_stats_t stats)
{
    printf("Column: %s\n", df->column_names[c]);
    printf("Count: %d\n", stats.count);
    printf("Mean: %.2f\n", stats.mean);
    printf("Std: %.2f\n", (stats.var > 0 ? sqrt(stats.var) : 0.0));
    printf("Min: %.2f\n", stats.min);
    printf("Max: %.2f\n", stats.max);
}

void df_describe(dataframe_t *df)
{
    int c = 0;
    column_stats_t stats;

    if (!df)
        return;
    for (c = 0; c < df->nb_columns; c++) {
        if ((df->column_types[c] == INT) ||
            (df->column_types[c] == UINT) ||
            (df->column_types[c] == FLOAT)) {
            stats = compute_column_stats(df, c);
            print_column_stats(df, c, stats);
        }
    }
}
