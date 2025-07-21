/*
** EPITECH PROJECT, 2024
** ia
** File description:
** dataframe.h
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_
    #define LINE_SIZE 4096

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    char ***data;
} dataframe_t;

typedef struct flags_s {
    int has_int;
    int has_bool;
    int has_float;
    int has_neg;
} flags_t;

typedef struct agg_accum_s {
    void **local_vals;
    int count;
} agg_accum_t;

typedef struct agg_params_s {
    int real_idx;
    int row;
} agg_params_t;

typedef struct group_ctx_s {
    dataframe_t *df;
    dataframe_t *new_df;
    int by_idx;
    char **unique_vals;
    int unique_count;
    void *(*agg_func)(void **, int);
} group_ctx_t;

typedef struct column_stats_s {
    int count;
    double sum;
    double min;
    double max;
    double mean;
    double var;
} column_stats_t;

typedef struct sort_context_s {
    dataframe_t *df;
    int col_idx;
    bool (*sort_func)(void *, void *);
} sort_context_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *df, const char *filename);
dataframe_t *df_head(dataframe_t *df, int nb_rows);
dataframe_t *df_tail(dataframe_t *df, int n);
dataframe_shape_t df_shape(dataframe_t *df);
void df_info(dataframe_t *df);
void df_describe(dataframe_t *df);
dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_func)(void *));
dataframe_t *df_sort(dataframe_t *df, const char *column,
    bool (*sort_func)(void *, void *));
dataframe_t *df_groupby(dataframe_t *df, const char *by, const char **cols,
    void *(*agg_func)(void **, int));
dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *));
dataframe_t *df_to_type(dataframe_t *df, const char *column,
    column_type_t dow);
void *df_get_value(dataframe_t *df, int row, const char *column);
void **df_get_values(dataframe_t *df, const char *column);
void **df_get_unique_values(dataframe_t *df, const char *column);
void df_free(dataframe_t *df);
column_type_t detect_column_type(char **vals, int nb_rows);
long long my_atoll(const char *s);
double my_atof(const char *s);
int find_column_index(dataframe_t *df, const char *column);
int is_int(const char *s);
int is_float(const char *s);
int is_bool(const char *s);
void fill_group_key(dataframe_t *new_df, char **unique_vals, int unique_count);
int aggregate_for_value(group_ctx_t *ctx, agg_params_t *params);
int count_grouped_cols(const char **to_agg);
group_ctx_t *setup_group_ctx(dataframe_t *df, const char *group_by,
    void *(*agg_func)(void **, int));
int finalize_grouped_df(group_ctx_t *ctx, const char **to_aggregate);
dataframe_t *create_grouped_df_from_ctx(dataframe_t *df,
    const char *group_by, const char **to_aggregate, group_ctx_t *ctx);
char **unique_strs(char **arr, int n, int *out);
int unique_str_count(char **arr, int n);
int fill_all_aggregations(group_ctx_t *ctx, const char **to_agg);
dataframe_t *init_df(void);
void clean_line(char *line);
char **split_line(char *line, const char *sep, int *count);

#endif
