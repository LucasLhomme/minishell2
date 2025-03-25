/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** pipe
*/

#include "my.h"
#include "lib.h"
#include <ctype.h>
#include <errno.h>

static int searching_bin_pipe(char *buffer, char **env, int in_fd, int out_fd)
{
    char **argv = my_str_to_word_array(buffer);
    char *path = NULL;

    if (argv == NULL || argv[0] == NULL)
        return 1;
    path = concas_command(argv);
    if (access(path, X_OK) == 0) {
        dup2(in_fd, STDIN_FILENO);
        dup2(out_fd, STDOUT_FILENO);
        close(in_fd == STDIN_FILENO ? -1 : in_fd);
        close(out_fd == STDOUT_FILENO ? -1 : out_fd);
        execute_bin(path, argv, env);
        exit(0);
    } else {
        free(path);
        for (int i = 0; argv[i] != NULL; i++)
            free(argv[i]);
        free(argv);
        return 1;
    }
}

static void execute_command(char *command, int in_fd,
    int out_fd, char **env)
{
    if (searching_bin_pipe(command, env, in_fd, out_fd) != 0) {
        my_printf("%s: Command not found.\n", command);
        return;
    }
}

static int create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    return 0;
}

static pid_t create_child_process(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }
    return pid;
}

static int execute_first_command(pid_t pid1, int pipefd[2],
    char *command1, char **env)
{
    if (pid1 == 0) {
        close(pipefd[0]);
        execute_command(command1, STDIN_FILENO, pipefd[1], env);
    }
    return 0;
}

static int execute_second_command(pid_t pid2, int pipefd[2],
    char *command2, char **env)
{
    if (pid2 == 0) {
        close(pipefd[1]);
        execute_command(command2, pipefd[0], STDOUT_FILENO, env);
    }
    return 0;
}

static int wait_for_children(pid_t pid1, pid_t pid2)
{
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

static int setup_and_execute_commands(int pipefd[2], char *command1,
    char *command2, char **env)
{
    pid_t pid1;
    pid_t pid2;

    pid1 = create_child_process();
    if (pid1 == -1)
        return 1;
    if (my_strcmp(command1, command2) == 1) {
        execute_first_command(pid1, pipefd, command1, env);
        pid2 = create_child_process();
        if (pid2 == -1)
        return 1;
        execute_second_command(pid2, pipefd, command2, env);
    } else
        execute_first_command(pid1, pipefd, command1, env);
    return 0;
}

int is_null_command(char *command1, char *command2)
{
    if (command1 == NULL || command2 == NULL) {
        my_printf("Invalid null command.\n");
        return 1;
    }
    if (command1[0] == '|' || command2[0] == '|') {
        my_printf("Invalid null command.\n");
        return 1;
    }
    return 0;
}

int simple_pipe(char *buffer, char **env)
{
    int pipefd[2];
    char *command1 = my_strtok(buffer, "|");
    char *command2 = my_strtok(NULL, "|");
    pid_t pid1 = -1;
    pid_t pid2 = -1;

    return is_null_command(command1, command2);
    command1 = trim_whitespace(command1);
    command2 = trim_whitespace(command2);
    if (create_pipe(pipefd) != 0)
        return 1;
    if (setup_and_execute_commands(pipefd, command1, command2, env) != 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait_for_children(pid1, pid2);
    return 0;
}
