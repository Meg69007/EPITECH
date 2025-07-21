/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>

typedef struct square_info_s {
    int max_size;
    int max_row;
    int max_col;
    int **dp;
    int rows;
    int cols;
} square_info_t;

void print_grid(char **grid);
void print_error(char *message);
int get_expected_lines(char *buffer, char **map_buffer);
char *get_first_line(char *buffer);
char *get_next_line_from_buffer(char **buffer);
char **read_file(char const *filename);
int get_file_size(char const *filename);
int open_file(char const *filename);
char *read_file_content(int fd, int size);
char *read_file_to_buffer(char const *filename);
int file_input(char ***grid, char *filename);
int map_generation(char ***grid, char **argv);
int process_arguments(int argc, char **argv, char ***grid);
int check_grid(char **grid, int expected_lines);
int main(int argc, char **argv);
void free_dp_table(square_info_t *info, int rows_allocated);
int allocate_dp_table(square_info_t *info);
int initialize_info(square_info_t *info, char **grid);
void update_square_info(square_info_t *info, char **grid, int i, int j);
int find_largest_square(char **grid);
int my_atoi(const char *str);
int my_strlen(char const *str);
void free_grid(char **grid);
int min(int a, int b, int c);
char **parse_grid(char *buffer, int expected_lines);
int my_getnbr(char const *str);
char **generate_map(char **argv);
char *generate_line(int size, char *pattern);
int check_line_lengths(char **grid);
int is_valid_char(char c);
int check_grid_chars(char **grid);
int get_grid_height(char **grid);
void mark_square(char **grid, square_info_t *info);
void free_info(square_info_t *info);
void fill_line(char *line, int size, char *pattern, int pattern_len);

#endif /* MY_H_ */
