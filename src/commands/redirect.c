/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** redirect
*/
#include "lib.h"
#include "my.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int redirect(char *buffer, char **env)
{
    char *command = my_strtok(buffer, ">");
    char *file = my_strtok(NULL, ">");
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid = fork();

    if (file == NULL || command == NULL) {
        my_printf("Missing name for redirect.\n");
        return 1;
    }
    file = trim_whitespace(file);
    command = trim_whitespace(command);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    if (pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    }
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        if (hand_command(command, env) == -1) {
            my_printf("%s: Command not found.\n", command);
            exit(1);
        }
        exit(0);
    } else {
        close(fd);
        waitpid(pid, NULL, 0);
    }
    return 0;
}