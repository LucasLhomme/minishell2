/*
** EPITECH PROJECT, 2024
** Mon H
** File description:
** Header avec les fonctions
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>

typedef int (*command_func_t)(char *, char **);

typedef struct handle_command_s {
    char *command;
    command_func_t func;
} handle_command_t;

#ifndef MY_H_
    #define MY_H_
char *cleaning_buffer(char *buffer);
int searching_bin(char *buffer, char **env);
int loop_terminal(char **env);
int hand_command(char *buffer, char **env);
int my_cd(char *command, char **env);
int loop_tty(char **env);
int my_env(char *buffer, char **env);
int my_setenv(char *buffer, char **env);
int new_value_env(char *name, char **env);
int over_value_env(char *name, char *value, char **env);
int my_unsetenv(char *name, char **env);
int my_isalpha(char c);
int execute_bin(char *path, char **argv, char **env);


#endif /* MY_H_ */
