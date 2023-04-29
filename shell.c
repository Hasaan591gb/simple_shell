#include "main.h"

void execute_command(char *line);
char *get_path(char *command);
int check_env(char **argv);
void cd_command(char **argv);
void check_exit(char **argv);

/**
 * main - reads commands from standard input and executes them
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}

		if (isatty(STDIN_FILENO) == 1)
			printf("# ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
				break;
			fprintf(stderr, "Error: %s\n", strerror(errno));
			continue;
		}
		else if (strcmp(line, "\n") == 0)
			continue;

		if (line != NULL)
			execute_command(line);
	}

	if (line != NULL)
		free(line);
	return (0);
}

/**
 * execute_command - executes a command
 * @line: the command to execute
 *
 * This function takes a command as input and executes it in a new process.
 * It uses the fork and execve functions to create a new process and execute
 * the command in the child process. The parent process waits for the child
 * process to complete using the wait function.
 */
void execute_command(char *line)
{
	char *argv[10] = {NULL};
	char *token;
	pid_t pid;
	int i = 0;

	/* Tokenize the input to remove the newline character */
	token = strtok(line, " \n");
	if (token == NULL)
		return;
	while (token != NULL && i < 9)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}

	if (strcmp(argv[0], "cd") == 0)
	{
		cd_command(argv);
		return;
	}
	else if (strcmp(argv[0], "setenv") == 0)
	{
		if (argv[1] && argv[2])
		{
			if (setenv(argv[1], argv[2], 1) == -1)
				fprintf(stderr, "Error: setenv failed\n");
		}
		else
			fprintf(stderr, "Error: setenv requires two arguments\n");
		return;
	}
	else if (strcmp(argv[0], "unsetenv") == 0)
	{
		if (argv[1])
		{
			if (unsetenv(argv[1]) == -1)
				fprintf(stderr, "Error: unsetenv failed\n");
		}
		else
			fprintf(stderr, "Error: unsetenv requires one argument\n");
		return;
	}
	check_exit(argv);

	if (check_env(argv) == 0)
		return;

	if (access(argv[0], X_OK) != 0)
		argv[0] = get_path(argv[0]);

	if (argv[0] == NULL)
		return;

	/* Create a new process */
	pid = fork();
	if (pid == -1)
		perror("Error: fork failed\n");
	else if (pid == 0)
	{
		/* Execute the command in the child process */
		execve(argv[0], argv, NULL);
		return;
	}
	else
		/* Wait for the child process to complete */
		wait(NULL);
}

/**
 * get_path - finds the full path of a command
 * @command: the command to find the full path for
 *
 * Return: the full path of the command if found, NULL otherwise
 */
char *get_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path;

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * check_env - checks if the first argument is "env" and prints the environment
 * @argv: the arguments to check
 *
 * Return: 0 if the first argument is "env", -1 otherwise
 */
int check_env(char **argv)
{
	int i;

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (0);
	}

	return (-1);
}

/**
 * cd_command - changes the current working directory
 * @argv: array of arguments passed to the cd command
 *
 * Description: If argv[1] is NULL, changes the current working directory to
 * the value of the HOME environment variable. If argv[1] is "-", changes the
 * current working directory to the value of the OLDPWD environment variable
 * and prints its value to stdout. Otherwise, changes the current working
 * directory to the value of argv[1]. Updates the OLDPWD and PWD environment
 * variables.
 */
void cd_command(char **argv)
{
	char *directory = NULL;
	char *home = NULL;
	char *oldpwd = NULL;
	char cwd[PATH_MAX];

	directory = argv[1];
	if (directory == NULL)
	{
		home = getenv("HOME");
		if (home != NULL)
			directory = home;
	}
	else if (strcmp(directory, "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (oldpwd != NULL)
		{
			directory = oldpwd;
			printf("%s\n", directory);
		}
	}

	if (directory != NULL)
	{
		if (chdir(directory) == -1)
			perror("Error: cd failed");
		else
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				setenv("PWD", cwd, 1);
		}
	}
}

/**
 * check_exit - checks if the first argument is "exit"
 * @argv: array of strings
 *
 * Return: void
 */
void check_exit(char **argv)
{
	int status;

	if (strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] != NULL)
			status = atoi(argv[1]);
		else
			status = EXIT_SUCCESS;
		exit(status);
	}
}
