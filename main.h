#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

void execute_command(char *line);
char *get_path(char *command);
int check_exit(char **argv);
int check_env(char **argv);
void cd_command(char **argv);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif
