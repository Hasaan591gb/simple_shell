#include "main.h"

void check_exit(char **argv, char *line, char *linecpy, int num_token);
void check_env(char **argv);

/**
 * main - reads commands from standard input and executes them
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL, *linecpy = NULL;
	char *delim = " \n";
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
		nread = _getline(&line, &len);
		if (nread == -1)
			break;

		linecpy = malloc(sizeof(char) * nread);
		if (linecpy == NULL)
			return (1);

		strcpy(linecpy, line);
		token = _strtok(linecpy, delim);
		while(token != NULL)
		{
			num_token++;
			token = _strtok(NULL, delim);
		}

		argv = malloc(sizeof(char *) * (num_token + 1));
		token = _strtok(line, delim);
		for(i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = _strtok(NULL, delim);
		}
		argv[i] = NULL;

		check_exit(argv, line, linecpy, num_token);
		check_env(argv);
		if (strcmp(argv[0], "env") != 0)
			execute(argv);

		for (i = 0; i <= num_token; i++)
			free(argv[i]);
		free(argv);
		free(linecpy);
	}

	free(line);
	return (0);
}

void check_exit(char **argv, char *line, char *linecpy, int num_token)
{
	int i, status;

	if (strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] != NULL)
			status = _atoi(argv[1]);
		else
			status = EXIT_SUCCESS;
		free(line);
		free(linecpy);
		for (i = 0; i <= num_token; i++)
			free(argv[i]);
		free(argv);

		exit(status);
	}
}

void check_env(char **argv)
{
	int i;

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
	}
}
