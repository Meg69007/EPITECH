#include <stdio.h>
#include <sys/stat.h>

long get_file_size(const char *filepath)
{
    struct stat st;

    if (stat(filepath, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

int main()
{
    const char *chemin_fichier = "example.txt";
    long taille = get_file_size(chemin_fichier);

    printf("La taille du fichier '%s' est de %ld octets.\n", chemin_fichier, taille);
    return 0;
}

#include <stdlib.h>
#include <string.h>

int min(int a, int b, int c)
{
    int min = (a < b) ? a : b;
    return ((min < c) ? min : c);
}

char *get_first_line(const char *buffer)
{
    int i = 0;
    char *line;

    while (buffer[i] && buffer[i] != '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    for (int j = 0; j < i; j++)
        line[j] = buffer[j];
    line[i] = '\0';
    return (line);
}

int is_valid_char(char c)
{
    return (c == '.' || c == 'o');
}

int get_grid_height(char **grid)
{
    int height = 0;

    while (grid[height])
        height++;
    return (height);
}

void fill_line(char *line, int size, const char *pattern)
{
    int pattern_len = strlen(pattern);
    int i = 0, j = 0;

    while (i < size) {
        line[i] = pattern[j];
        i++;
        j = (j + 1) % pattern_len;
    }
    line[size] = '\0';
}

void free_grid(char **grid)
{
    int i = 0;

    while (grid[i]) {
        free(grid[i]);
        i++;
    }
    free(grid);
}

int **initialize_dp_table(int rows, int cols)
{
    int **dp = malloc(sizeof(int *) * rows);
    if (!dp)
        return (NULL);

    for (int i = 0; i < rows; i++) {
        dp[i] = malloc(sizeof(int) * cols);
        if (!dp[i]) {
            for (int j = 0; j < i; j++)
                free(dp[j]);
            free(dp);
            return (NULL);
        }
        for (int j = 0; j < cols; j++)
            dp[i][j] = 0;
    }
    return (dp);
}

int compute_square_size(int dp_top, int dp_left, int dp_diag)
{
    return min(dp_top, dp_left, dp_diag) + 1;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void read_and_print_file(const char filepath) {
    FILEfile = fopen(filepath, "r");
    if (file == NULL) {
        return;
    }

    struct stat st;
    if (stat(filepath, &st) != 0) {
        fclose(file);
        return;
    }

    size_t filesize = st.st_size;
    char buffer = (char)malloc(sizeof(char) * (filesize + 1));
    if (buffer == NULL) {
        fclose(file);
        return;
    }

    fread(buffer, sizeof(char), filesize, file);
    buffer[filesize] = '\0';

    printf("%s", buffer);

    free(buffer);
    fclose(file);
}


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void read_and_print_file(const char filepath)
{
    int fd = open(filepath, O_RDONLY);
    struct stat st;
    fstat(fd, &st);

    char *buffer = malloc(st.st_size);
    read(fd, buffer, st.st_size);
    printf("%.*s", (int)st.st_size, buffer);
    free(buffer);
    close(fd);
}
