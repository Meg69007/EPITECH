/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** o_exec.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mysh.h"

char *search_in_path(char *copy, const char *cmd)
{
    char *token = strtok(copy, ":");
    char *candidate = NULL;

    while (token) {
        candidate = build_path(token, cmd);
        if (candidate && access(candidate, X_OK) == 0)
            return candidate;
        free(candidate);
        token = strtok(NULL, ":");
    }
    return NULL;
}

char *build_path(const char *dir, const char *cmd)
{
    int size = my_strlen(dir) + my_strlen(cmd) + 2;
    char *res = malloc(sizeof(char) * size);
    int i = 0;

    if (!res)
        return NULL;
    while (i < size) {
        res[i] = '\0';
        i++;
    }
    my_strcat(res, dir);
    my_strcat(res, "/");
    my_strcat(res, cmd);
    return res;
}
