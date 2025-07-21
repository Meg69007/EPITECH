/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** path_utils.c
*/

#include "../my.h"

char **allocate_paths(int argc)
{
    char **paths = malloc(sizeof(char *) * argc);

    if (!paths) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    return paths;
}

int is_option(const char *arg)
{
    return (arg[0] == '-' && arg[1] != '\0');
}

void add_path(path_info_t *path_info, const char *arg)
{
    path_info->paths[path_info->path_count] = (char *)arg;
    path_info->path_count++;
}

void check_default_path(path_info_t *path_info)
{
    if (path_info->path_count == 0) {
        path_info->paths[0] = ".";
        path_info->path_count = 1;
    }
}
