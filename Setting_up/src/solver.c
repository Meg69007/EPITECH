/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** solver.c
*/

#include "../my.h"

int check_line_chars(char *line)
{
    int j = 0;

    for (j = 0; line[j]; j++) {
        if (!is_valid_char(line[j]))
            return (84);
    }
    return (0);
}

int check_grid_chars(char **grid)
{
    int i = 0;
    int result = 0;

    if (!grid)
        return (84);
    for (i = 0; grid[i]; i++) {
        result = check_line_chars(grid[i]);
        if (result == 84)
            return (84);
    }
    return (0);
}

int get_grid_height(char **grid)
{
    int height = 0;

    if (!grid)
        return (0);
    while (grid[height])
        height++;
    return (height);
}

void mark_square(char **grid, square_info_t *info)
{
    int i = 0;
    int j = 0;
    int size = info->max_size;
    int row_start = info->max_row - size + 1;
    int col_start = info->max_col - size + 1;

    for (i = row_start; i <= info->max_row; i++) {
        for (j = col_start; j <= info->max_col; j++) {
            grid[i][j] = 'x';
        }
    }
}

void free_info(square_info_t *info)
{
    int i = 0;

    if (!info || !info->dp)
        return;
    for (i = 0; i < info->rows; i++) {
        free(info->dp[i]);
    }
    free(info->dp);
    info->dp = NULL;
}
