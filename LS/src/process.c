/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** process.c
*/

#include "../my.h"

void process_path(const char *path, options_t opts)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == -1) {
        my_puterror("Error: stat failed\n");
        return;
    }
    if (S_ISDIR(path_stat.st_mode)) {
        handle_directory(path, opts);
    } else {
        handle_file(path, opts);
    }
}

void handle_directory(const char *path, options_t opts)
{
    if (opts.d) {
        display_path_or_info(path, opts);
    } else {
        list_directory(path, opts);
    }
}

void handle_file(const char *path, options_t opts)
{
    display_path_or_info(path, opts);
}

void display_path_or_info(const char *path, options_t opts)
{
    if (opts.l) {
        display_file_info(path, NULL);
    } else {
        my_putstr(path);
        my_putstr("\n");
    }
}

char *concat_path(const char *path, const char *name)
{
    int len_path = my_strlen(path);
    int len_name = my_strlen(name);
    int need_slash = (len_path > 0 && path[len_path - 1] != '/');
    int total_length = len_path + need_slash + len_name + 1;
    char *full_path = malloc(total_length);

    if (full_path == NULL) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    my_strcpy(full_path, path);
    if (need_slash) {
        my_strcat(full_path, "/");
    }
    my_strcat(full_path, name);
    return full_path;
}
