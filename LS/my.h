/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

    #include <sys/types.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <pwd.h>
    #include <grp.h>
    #include <time.h>
    #include <errno.h>

typedef struct {
    int l;
    int upper_r;
    int d;
    int r;
    int t;
} options_t;

typedef struct {
    int argc;
    char **argv;
} arguments_t;

typedef struct {
    char **paths;
    int path_count;
} path_info_t;

typedef struct {
    char option_char;
    void (*set_option)(options_t *);
} option_map_t;

typedef struct {
    char *path;
    struct dirent *entry;
} file_entry_t;

int main(int argc, char **argv);
void parse_options(arguments_t args, options_t *opts, path_info_t *path_info);
char **allocate_paths(int argc);
int is_option(const char *arg);
void add_path(path_info_t *path_info, const char *arg);
void check_default_path(path_info_t *path_info);
void process_path(const char *path, options_t opts);
void handle_directory(const char *path, options_t opts);
void handle_file(const char *path, options_t opts);
void display_path_or_info(const char *path, options_t opts);
void list_directory(const char *path, options_t opts);
int read_directory_entries(DIR *dir, file_entry_t **entries, const char *path);
void sort_entries(file_entry_t **entries, int count, options_t opts);
void display_entries(file_entry_t **entries, int count, options_t opts);
void recursive_list(file_entry_t **entries, int count, options_t opts);
void free_entries(file_entry_t **entries, int count);
int my_putstr(const char *str);
void my_puterror(const char *str);
int my_put_nbr(int nb);
int my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);
void *my_memcpy(void *dest, const void *src, unsigned int n);
char *concat_path(const char *path, const char *name);
int compare_time(const void *a, const void *b);
int compare_name(const void *a, const void *b);
time_t get_modification_time(file_entry_t *file);
void display_permissions(mode_t mode);
void display_file_info(const char *full_path, struct dirent *entry);
void reverse_entries(file_entry_t **entries, int count);
int directory(const char *name);
void process_entry(file_entry_t *entry, options_t opts);
void my_putchar(char c);

#endif /* MY_H */
