#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

void execute_command(char *line);

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
		if (isatty(STDIN_FILENO) == 1)
			printf("# ");
		else
			fprintf(stderr, "Error: fd not terminal\n");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				printf("end of file");
				break;
			}
			else
			{
				fprintf(stderr, "Error: %s\n", strerror(errno));
				continue;
			}
		}
		else if (strcmp(line, "\n") == 0)
			continue;

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
	char *argv[] = {NULL, NULL};
	pid_t pid;

	/* Tokenize the input to remove the newline character */
	argv[0] = strtok(line, "\n");

	/* Create a new process */
	pid = fork();
	if (pid == -1)
		perror("Error: fork failed\n");
	else if (pid == 0)
	{
		/* Execute the command in the child process */
		execve(argv[0], argv, NULL);
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
	}
	else
		/* Wait for the child process to complete */
		wait(NULL);
}
