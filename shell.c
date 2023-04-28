#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

void execute_command(char **argv);

/**
 * main - reads commands from standard input and executes them
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	char *linecpy = NULL;
	char *delim = " \n";
	size_t len = 0;
	ssize_t nread;
	char **argv;
	char *token;
	int num_token = 0;
	int i;

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

		linecpy = malloc(sizeof(char) * nread);
		if (linecpy == NULL)
			return (1);

		strcpy(linecpy, line);
		token = strtok(linecpy, delim);
		while (token != NULL)
		{
			num_token++;
			token = strtok(NULL, delim);
		}

		argv = malloc(sizeof(char *) * (num_token + 1));
		token = strtok(line, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		execute_command(argv);

		for (i = 0; i < num_token; i++)
			free(argv[i]);
		free(argv);
		free(linecpy);
	}

	if (line != NULL)
		free(line);
	return (0);
}

/**
 * execute_command - executes a command
 * @argv: the command to execute
 *
 * This function takes a command as input and executes it in a new process.
 * It uses the fork and execve functions to create a new process and execute
 * the command in the child process. The parent process waits for the child
 * process to complete using the wait function.
 */
void execute_command(char **argv)
{
	pid_t pid;

	if (argv[0] == NULL)
	{
		perror("Error: strtok failed\n");
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
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		return;
	}
	else
		/* Wait for the child process to complete */
		wait(NULL);
}
