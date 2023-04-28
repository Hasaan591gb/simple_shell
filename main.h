#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

void execute_command(char *line);
char *get_path(char *command);
void check_exit(char **argv);
void check_env(char **argv);
ssize_t _getline(char **lineptr, size_t *n);
ssize_t read_line(char *buffer, size_t *start,
		size_t end, char **lineptr, size_t *n);

#endif
