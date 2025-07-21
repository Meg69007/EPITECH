/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** options.c
*/

#include "../my.h"

static void set_option_l(options_t *opts)
{
    opts->l = 1;
}

static void set_option_upper_r(options_t *opts)
{
    opts->upper_r = 1;
}

static void set_option_d(options_t *opts)
{
    opts->d = 1;
}

static void set_option_r(options_t *opts)
{
    opts->r = 1;
}

static void set_option_t(options_t *opts)
{
    opts->t = 1;
}

static const option_map_t option_map[] = {
    {'l', set_option_l},
    {'R', set_option_upper_r},
    {'d', set_option_d},
    {'r', set_option_r},
    {'t', set_option_t},
    {'\0', NULL}
};

static void check_option(char c, options_t *opts)
{
    int i = 0;

    while (option_map[i].option_char != '\0') {
        if (option_map[i].option_char == c) {
            option_map[i].set_option(opts);
            return;
        }
        i++;
    }
    my_puterror("Invalid option\n");
    exit(84);
}

static void parse_options_in_arg(const char *arg, options_t *opts)
{
    int j = 1;

    while (arg[j]) {
        check_option(arg[j], opts);
        j++;
    }
}

void parse_options(arguments_t args, options_t *opts, path_info_t *path_info)
{
    int i = 1;

    path_info->path_count = 0;
    path_info->paths = allocate_paths(args.argc);
    while (i < args.argc) {
        if (is_option(args.argv[i]))
            parse_options_in_arg(args.argv[i], opts);
        else
            add_path(path_info, args.argv[i]);
        i++;
    }
    check_default_path(path_info);
}
