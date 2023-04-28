#include "main.h"

void execute_command(char *line);
char *get_path(char *command);
int check_env(char **argv);

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
	{
		perror("Error: strtok failed\n");
		return;
	}
	while (token != NULL && i < 9)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}

	if (check_env(argv) == 0)
		return;

	if (access(argv[0], X_OK) != 0)
		argv[0] = get_path(argv[0]);

	if (argv[0] == NULL)
	{
		perror("invalid command");
		return;
	}

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
