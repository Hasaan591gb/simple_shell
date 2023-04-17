#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	char *line = NULL;
	pid_t child_pid;
	ssize_t nread;
	size_t len = 0;
	char *args[2];
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		line[nread - 1] = '\0';

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(1);
		}
		if (child_pid == 0)
		{
			args[0] = line;
			args[1] = NULL;
			execve(args[0], args, NULL);
			perror("Error");
			exit(1);
		}
		else
			wait(&status);
	}

	free(line);
	return (0);
}
