/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** main.c
*/

#include "../my.h"
#include <unistd.h>

int file_input(char ***grid, char *filename)
{
    *grid = read_file(filename);
    if (!(*grid)) {
        print_error("Error reading file\n");
        return (84);
    }
    return (0);
}

int map_generation(char ***grid, char **argv)
{
    *grid = generate_map(argv);
    if (!(*grid)) {
        print_error("Error generating map\n");
        return (84);
    }
    return (0);
}

int process_arguments(int argc, char **argv, char ***grid)
{
    int result = 0;

    if (argc == 2)
        result = file_input(grid, argv[1]);
    else if (argc == 3)
        result = map_generation(grid, argv);
    else {
        print_error("Usage: ./setting_up <file>\n");
        print_error("Or: ./setting_up size pattern\n");
        return (84);
    }
    return (result);
}

int check_grid(char **grid, int expected_lines)
{
    int lines = 0;
    int result = 0;

    if (!grid)
        return (84);
    while (grid[lines])
        lines++;
    if (lines != expected_lines || lines == 0)
        return (84);
    result = check_line_lengths(grid);
    if (result == 84)
        return (84);
    result = check_grid_chars(grid);
    if (result == 84)
        return (84);
    return (0);
}

int main(int argc, char **argv)
{
    char **grid = NULL;
    int result = 0;

    result = process_arguments(argc, argv, &grid);
    if (result == 84)
        return (84);
    result = check_grid(grid, get_grid_height(grid));
    if (result == 84) {
        free_grid(grid);
        return (84);
    }
    result = find_largest_square(grid);
    if (result == 84) {
        free_grid(grid);
        return (84);
    }
    print_grid(grid);
    free_grid(grid);
    return (0);
}
