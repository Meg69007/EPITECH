/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** map.c
*/

#include <stdlib.h>
#include "../my.h"

void free_dp_table(square_info_t *info, int rows_allocated)
{
    int k = 0;

    for (k = 0; k < rows_allocated; k++) {
        free(info->dp[k]);
    }
    free(info->dp);
    info->dp = NULL;
}

int allocate_dp_table(square_info_t *info)
{
    int i = 0;
    int j = 0;

    info->dp = malloc(sizeof(int *) * info->rows);
    if (!info->dp)
        return (84);
    for (i = 0; i < info->rows; i++) {
        info->dp[i] = malloc(sizeof(int) * info->cols);
        if (!info->dp[i]) {
            free_dp_table(info, i);
            return (84);
        }
        for (j = 0; j < info->cols; j++) {
            info->dp[i][j] = 0;
        }
    }
    return (0);
}

int initialize_info(square_info_t *info, char **grid)
{
    int result = 0;

    info->rows = 0;
    while (grid[info->rows])
        info->rows++;
    info->cols = my_strlen(grid[0]);
    info->max_size = 0;
    info->max_row = 0;
    info->max_col = 0;
    result = allocate_dp_table(info);
    if (result == 84) {
        return (84);
    }
    return (0);
}

void update_square_info(square_info_t *info, char **grid, int i, int j)
{
    if (grid[i][j] == '.') {
        if (i == 0 || j == 0)
            info->dp[i][j] = 1;
        else
            info->dp[i][j] = min(info->dp[i - 1][j],
            info->dp[i][j - 1], info->dp[i - 1][j - 1]) + 1;
        if (info->dp[i][j] > info->max_size) {
            info->max_size = info->dp[i][j];
            info->max_row = i;
            info->max_col = j;
        }
    } else {
        info->dp[i][j] = 0;
    }
}

int find_largest_square(char **grid)
{
    square_info_t info;
    int i = 0;
    int j = 0;
    int init_result = 0;

    init_result = initialize_info(&info, grid);
    if (init_result == 84) {
        print_error("Error initializing info\n");
        return (84);
    }
    for (i = 0; i < info.rows; i++) {
        for (j = 0; j < info.cols; j++) {
            update_square_info(&info, grid, i, j);
        }
    }
    mark_square(grid, &info);
    free_info(&info);
    return (0);
}
