/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** entry.c
*/

#include "../my.h"

int add_entry(file_entry_t **entries,
    int count, const char *path, struct dirent *entry)
{
    char *path_copy = malloc(my_strlen(path) + 1);

    entries[count] = malloc(sizeof(file_entry_t));
    if (!entries[count]) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    if (!path_copy) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    entries[count]->path = my_strcpy(path_copy, path);
    entries[count]->entry = malloc(sizeof(struct dirent));
    if (!entries[count]->entry) {
        my_puterror("Error: malloc failed\n");
        exit(84);
    }
    my_memcpy(entries[count]->entry, entry, sizeof(struct dirent));
    return count + 1;
}

int read_directory_entries(DIR *dir, file_entry_t **entries, const char *path)
{
    struct dirent *entry;
    int count = 0;

    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.') {
            count = add_entry(entries, count, path, entry);
        }
        entry = readdir(dir);
    }
    return count;
}

static int partition(file_entry_t **array, int low, int high,
    int (*cmp)(const void *, const void *))
{
    file_entry_t *pivot = array[high];
    int i = low - 1;
    int j;
    file_entry_t *temp;

    for (j = low; j < high; j++) {
        if (cmp(&array[j], &pivot) <= 0) {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

static void quicksort(file_entry_t **array, int low, int high,
    int (*cmp)(const void *, const void *))
{
    int pi;

    if (low < high) {
        pi = partition(array, low, high, cmp);
        quicksort(array, low, pi - 1, cmp);
        quicksort(array, pi + 1, high, cmp);
    }
}

static void my_qsort(file_entry_t **array, int count,
    int (*cmp)(const void *, const void *))
{
    quicksort(array, 0, count - 1, cmp);
}

void sort_entries(file_entry_t **entries, int count, options_t opts)
{
    if (opts.t)
        my_qsort(entries, count, compare_time);
    else
        my_qsort(entries, count, compare_name);
    if (opts.r)
        reverse_entries(entries, count);
}

void display_entries(file_entry_t **entries, int count, options_t opts)
{
    int i = 0;
    char *full_path;

    while (i < count) {
        full_path = concat_path(entries[i]->path, entries[i]->entry->d_name);
        if (!full_path) {
            my_puterror("Error: malloc failed\n");
            exit(84);
        }
        if (opts.l) {
            display_file_info(full_path, entries[i]->entry);
        } else {
            my_putstr(entries[i]->entry->d_name);
            my_putstr("\n");
        }
        free(full_path);
        i++;
    }
}
