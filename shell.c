#include <stdio.h>
#include <string.h>
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
	char *line = NULL, *linecpy = NULL;
	char *delim = " \n";
	pid_t child_pid;
	ssize_t nread;
	size_t len = 0;
	char **argv;
	int i;
	char *token;
	int num_token = 0;

	/* read commands from standard input */
	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		linecpy = malloc(sizeof(char) * nread);
		if (linecpy == NULL)
			return (1);

		strcpy(linecpy, line);
		token = strtok(linecpy, delim);
		while(token != NULL)
		{
			num_token++;
			token = strtok(NULL, delim);
		}

		argv = malloc(sizeof(char *) * (num_token + 1));
		token = strtok(line, delim);
		for(i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		execute(argv);

		for (i = 0; i <= num_token; i++)
			free(argv[i]);
		free(argv);
		free(linecpy);
	}

	free(line);
	return (0);
}
