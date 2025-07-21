/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** display_utils.c
*/

#include "../my.h"

static void set_char(char *permissions, mode_t mode)
{
    if (S_ISDIR(mode))
        permissions[0] = 'd';
    else if (S_ISLNK(mode))
        permissions[0] = 'l';
    else
        permissions[0] = '-';
}

static void set_bits(char *permissions, mode_t mode)
{
    char *perm_chars = "rwxrwxrwx";
    mode_t modes[] = {
        S_IRUSR, S_IWUSR, S_IXUSR,
        S_IRGRP, S_IWGRP, S_IXGRP,
        S_IROTH, S_IWOTH, S_IXOTH
    };
    int i;

    for (i = 0; i < 9; i++) {
        if (mode & modes[i])
            permissions[i + 1] = perm_chars[i];
        else
            permissions[i + 1] = '-';
    }
}

void display_permissions(mode_t mode)
{
    char permissions[11] = "----------";

    set_char(permissions, mode);
    set_bits(permissions, mode);
    my_putstr(permissions);
    my_putstr(" ");
}

void display_user_group(struct stat *file_stat)
{
    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);

    if (pw != NULL)
        my_putstr(pw->pw_name);
    else
        my_putstr("?");
    my_putstr(" ");
    if (gr != NULL)
        my_putstr(gr->gr_name);
    else
        my_putstr("?");
    my_putstr(" ");
}

void display_time(struct stat *file_stat)
{
    char *time_str = ctime(&file_stat->st_mtime);

    if (time_str != NULL) {
        time_str[my_strlen(time_str) - 1] = '\0';
        my_putstr(time_str);
        my_putstr(" ");
    }
}

static void display_links(struct stat *file_stat)
{
    my_put_nbr(file_stat->st_nlink);
    my_putstr(" ");
}

static void display_size(struct stat *file_stat)
{
    my_put_nbr(file_stat->st_size);
    my_putstr(" ");
}

static void display_name(const char *full_path, struct dirent *entry)
{
    if (entry != NULL)
        my_putstr(entry->d_name);
    else
        my_putstr(full_path);
    my_putstr("\n");
}

void display_file_info(const char *full_path, struct dirent *entry)
{
    struct stat file_stat;

    if (lstat(full_path, &file_stat) == -1) {
        my_puterror("Error: lstat failed\n");
        return;
    }
    display_permissions(file_stat.st_mode);
    display_links(&file_stat);
    display_user_group(&file_stat);
    display_size(&file_stat);
    display_time(&file_stat);
    display_name(full_path, entry);
}
