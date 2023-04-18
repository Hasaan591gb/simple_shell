#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * main - reads commands from standard input and executes them
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	pid_t child_pid;
	ssize_t nread;
	size_t len = 0;
	char *args[2];
	int status;

	/* read commands from standard input */
	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		line[nread - 1] = '\0';

		/* create a child process to execute the command */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(1);
		}
		if (child_pid == 0)
		{
			/* execute the command in the child process */
			args[0] = line;
			args[1] = NULL;
			execve(args[0], args, NULL);
			perror("Error");
			exit(1);
		}
		else
			/* wait for the child process to complete */
			wait(&status);
	}

	free(line);
	return (0);
}
