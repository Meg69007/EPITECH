/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** time_utils.c
*/

#include "../my.h"

time_t get_modification_time(file_entry_t *file)
{
    struct stat file_stat;
    char *full_path;
    time_t mtime;

    full_path = concat_path(file->path, file->entry->d_name);
    if (full_path == NULL) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    if (lstat(full_path, &file_stat) == -1) {
        free(full_path);
        return 0;
    }
    mtime = file_stat.st_mtime;
    free(full_path);
    return mtime;
}

int compare_time(const void *a, const void *b)
{
    file_entry_t *file_a = *(file_entry_t **)a;
    file_entry_t *file_b = *(file_entry_t **)b;
    time_t mtime_a = get_modification_time(file_a);
    time_t mtime_b = get_modification_time(file_b);

    if (mtime_b > mtime_a)
        return 1;
    else if (mtime_b < mtime_a)
        return -1;
    else
        return compare_name(a, b);
}

int compare_name(const void *a, const void *b)
{
    file_entry_t *file_a = *(file_entry_t **)a;
    file_entry_t *file_b = *(file_entry_t **)b;

    return my_strcmp(file_a->entry->d_name, file_b->entry->d_name);
}
