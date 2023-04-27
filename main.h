#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

void execute(char **argv);
void execute_command(char *full_command, char **argv);
char *get_path(char *command);
void check_exit(char **argv, char *line, char *linecpy, int num_token);
void check_env(char **argv);
ssize_t _getline(char **lineptr, size_t *n);
ssize_t read_line(char *buffer, size_t *start,
		size_t end, char **lineptr, size_t *n);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void cd_command(char **argv);

#endif
