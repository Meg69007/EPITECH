/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** entry_utils.c
*/

#include "../my.h"

void recursive_list(file_entry_t **entries, int count, options_t opts)
{
    int i = 0;

    while (i < count) {
        process_entry(entries[i], opts);
        i++;
    }
}

void reverse_entries(file_entry_t **entries, int count)
{
    int i = 0;
    file_entry_t *temp;

    while (i < count / 2) {
        temp = entries[i];
        entries[i] = entries[count - i - 1];
        entries[count - i - 1] = temp;
        i++;
    }
}

void free_entries(file_entry_t **entries, int count)
{
    int i = 0;

    while (i < count) {
        free(entries[i]->entry);
        free(entries[i]->path);
        free(entries[i]);
        i++;
    }
    free(entries);
}

void process_entry(file_entry_t *entry, options_t opts)
{
    char *full_path;
    struct stat entry_stat;

    full_path = concat_path(entry->path, entry->entry->d_name);
    if (!full_path) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    if (lstat(full_path, &entry_stat) == -1) {
        free(full_path);
        return;
    }
    if (S_ISDIR(entry_stat.st_mode) && directory(entry->entry->d_name)) {
        my_putstr("\n");
        list_directory(full_path, opts);
    }
    free(full_path);
}
