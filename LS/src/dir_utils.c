/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** dir_utils.c
*/

#include "../my.h"

DIR *open_directory(const char *path)
{
    DIR *dir = opendir(path);

    if (dir == NULL) {
        my_puterror("Error: opendir failed\n");
        return NULL;
    }
    return dir;
}

file_entry_t **allocate_entries(size_t size)
{
    file_entry_t **entries = malloc(sizeof(file_entry_t *) * size);

    if (entries == NULL) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    return entries;
}

void list_directory(const char *path, options_t opts)
{
    DIR *dir = open_directory(path);
    file_entry_t **entries;
    int count;

    if (dir == NULL)
        return;
    entries = allocate_entries(1024);
    count = read_directory_entries(dir, entries, path);
    closedir(dir);
    sort_entries(entries, count, opts);
    if (opts.upper_r || opts.d || count > 1) {
        my_putstr(path);
        my_putstr(":\n");
    }
    display_entries(entries, count, opts);
    if (opts.upper_r) {
        recursive_list(entries, count, opts);
    }
    free_entries(entries, count);
}

int directory(const char *name)
{
    return (my_strcmp(name, ".") != 0 && my_strcmp(name, "..") != 0);
}
