/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** file.c
*/

#include "../my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int get_file_size(char const *filename)
{
    struct stat st;

    if (stat(filename, &st) == -1)
        return (-1);
    return (st.st_size);
}

int open_file(char const *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
        return (-1);
    return (fd);
}

char *read_file_content(int fd, int size)
{
    char *buffer = NULL;
    int bytes_read = 0;

    buffer = malloc(size + 1);
    if (!buffer)
        return (NULL);
    bytes_read = read(fd, buffer, size);
    if (bytes_read <= 0) {
        free(buffer);
        return (NULL);
    }
    buffer[bytes_read] = '\0';
    return (buffer);
}

char *read_file_to_buffer(char const *filename)
{
    int size = 0;
    int fd = 0;
    char *buffer = NULL;

    size = get_file_size(filename);
    if (size == -1)
        return (NULL);
    fd = open_file(filename);
    if (fd == -1)
        return (NULL);
    buffer = read_file_content(fd, size);
    close(fd);
    return (buffer);
}
