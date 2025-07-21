/*
** EPITECH PROJECT, 2024
** ia
** File description:
** utils_s.c
*/

#include "dataframe.h"

int is_int(const char *s)
{
    int i = 0;

    if (!s)
        return (0);
    if (!s[0])
        return (0);
    if (s[0] == '-' || s[0] == '+')
        i++;
    for (; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9')
            return (0);
    }
    return (1);
}

static int get_char_status(char c)
{
    if (c == '.')
        return 1;
    if (c >= '0' && c <= '9')
        return 0;
    return -1;
}

int is_float(const char *s)
{
    int i = 0;
    int dot_count = 0;
    int status;

    if (!s || s[0] == '\0')
        return (0);
    if (s[0] == '-' || s[0] == '+')
        i++;
    for (; s[i] != '\0'; i++) {
        status = get_char_status(s[i]);
        if (status == -1)
            return (0);
        dot_count += status;
        if (dot_count > 1)
            return (0);
    }
    return (dot_count == 1);
}

int is_bool(const char *s)
{
    if (!s)
        return (0);
    if (!strcasecmp(s, "true") || !strcasecmp(s, "false"))
        return (1);
    return (0);
}

long long my_atoll(const char *s)
{
    long long r = 0;
    int sign = 1;
    int i = 0;

    if (!s)
        return (0);
    if (s[0] == '-') {
        sign = -1;
        i++;
    }
    for (; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9')
            break;
        r = r * 10 + (s[i] - '0');
    }
    return (r * sign);
}

static double parse_fraction(const char *s)
{
    double frac = 0;
    double div = 1;
    int i = 0;

    while (s[i] && s[i] >= '0' && s[i] <= '9') {
        frac = frac * 10 + (s[i] - '0');
        div *= 10;
        i++;
    }
    return (frac / div);
}

static double parse_integer_part(const char *s, int *i)
{
    double r = 0;

    while (s[*i] && s[*i] != '.') {
        if (s[*i] < '0' || s[*i] > '9')
            break;
        r = r * 10 + (s[*i] - '0');
        (*i)++;
    }
    return (r);
}

double my_atof(const char *s)
{
    int i = 0;
    int sign = 1;
    double r = 0;
    double frac = 0;

    if (!s)
        return (0);
    if (s[0] == '-') {
        sign = -1;
        i++;
    } else {
        if (s[0] == '+')
            i++;
    }
    r = parse_integer_part(s, &i);
    if (s[i] == '.')
        frac = parse_fraction(s + i + 1);
    return (sign * (r + frac));
}
