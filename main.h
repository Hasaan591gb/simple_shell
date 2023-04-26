#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

void execute(char **argv);
char *get_path(char *command);
void check_exit(char **argv, char *line, char *linecpy, int num_token);
void check_env(char **argv);
ssize_t _getline(char **lineptr, size_t *n);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);

#endif
