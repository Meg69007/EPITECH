/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** main.c
*/

#include <stdlib.h>
#include <signal.h>
#include "mysh.h"

static void handle_sigint(int sig)
{
    (void)sig;
    my_puterr("\n");
}

int main(int ac, char **av, char **envp)
{
    char **env_cpy = NULL;

    (void)ac;
    (void)av;
    env_cpy = dup_environment(envp);
    if (env_cpy == NULL) {
        my_puterr("Error: environment.\n");
        return 84;
    }
    signal(SIGINT, handle_sigint);
    shell_loop(env_cpy);
    free_array(env_cpy);
    return 0;
}
