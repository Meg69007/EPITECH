/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** main.c
*/

#include "../my.h"

int main(int argc, char **argv)
{
    options_t opts = { 0 };
    path_info_t path_info;
    arguments_t args = {argc, argv};
    int i = 0;

    parse_options(args, &opts, &path_info);
    while (i < path_info.path_count) {
        process_path(path_info.paths[i], opts);
        if (i < path_info.path_count - 1)
            my_putstr("\n");
        i++;
    }
    free(path_info.paths);
    return 0;
}
