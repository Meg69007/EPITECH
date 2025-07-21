/*
** EPITECH PROJECT, 2024
** delivery
** File description:
** mysh.h
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef MYSH_H_
    #define MYSH_H_
    #define EXIT_SHELL 2

typedef struct s_cmd {
    char **argv;
    char *infile;
    char *outfile;
    int append_out;
    struct s_cmd *next;
} cmd_t;

typedef struct s_chain {
    cmd_t *cmds;
    int is_or;
    struct s_chain *next;
} chain_t;

typedef struct s_pipeline {
    cmd_t *cmds;
    struct s_pipeline *next;
} pipeline_t;

void shell_loop(char **env_cpy);
char **parse_command(char *line);
int is_builtin_command(const char *cmd);
int exec_builtin(char **args, char ***env);
int builtin_cd(char **args, char ***env);
int builtin_env(char **args, char **env);
int builtin_setenv(char **args, char ***env);
int builtin_unsetenv(char **args, char ***env);
int builtin_exit(char **args);
int exec_command(char **args, char **env);
void exec_child(char **args, char **env);
int handle_wait(pid_t pid);
char *check_direct_path(const char *cmd);
char *find_in_path(const char *cmd, char **env);
char *search_in_path(char *copy, const char *cmd);
char *build_path(const char *dir, const char *cmd);
int set_env_var_deep(char ***envp, const char *name, const char *value);
int unset_env_var_deep(char ***envp, const char *name);
int find_var_index(char **envp, const char *name);
void my_puterr(const char *msg);
int my_strlen(const char *s);
char *my_strcat(char *dest, const char *src);
char *my_strchr(const char *s, int c);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strdup(const char *src);
int my_atoi(const char *str);
char *my_strcpy(char *dest, const char *src);
int my_strcmp_len(const char *s1, const char *s2, int len);
int count_env_line(char **envp);
void free_array(char **arr);
char *my_strdup_safe(const char *src);
int partial_free_array(char **arr, int limit);
char **allocate_new_env(int size);
int copy_skip_idx(char ***envp, char **dup, int old_count, int var_ind);
char **deep_dup_env(char **envp, int new_size);
char **dup_environment(char **envp);
char *my_getenv(char **envp, const char *name);
int apply_redirections(cmd_t *c);
int exec_pipeline(cmd_t *c, char ***env);
pipeline_t *parse_line(char *line);
pipeline_t *assemble_pipelines(char **blocks);
void add_pip(pipeline_t **first, pipeline_t **last, pipeline_t *node);
pipeline_t *process_block(char *block);
void parse_redirs(char **arr, cmd_t *c);
pipeline_t *process_block(char *block);
cmd_t *alloc_cmd(void);
pipeline_t *build_pipeline_from_chain(chain_t *cchain);
chain_t *parse_or_chain(char *blk);
pipeline_t *build_pipeline_from_chain(chain_t *cchain);
int add_node_if(chain_t *cchain, pipeline_t **first, pipeline_t **last);
char **split_semicolons(char *line);
char **split_or(char *blk);
char **split_tokens(char *s, const char *del);
pipeline_t *create_pipeline_node(chain_t *cchain);

#endif
