#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * search_path - searches for a command in the system PATH
 * @path: the system PATH
 * @command: the command to search for
 *
 * Return: 0 if found, 1 if not found
 */
int search_path(char *path, char *command)
{
	struct stat st;
	char *token, *fullpath;

	/* search for the command in each directory of the PATH */
	token = strtok(path, ":");
	while (token)
	{
		fullpath = malloc(strlen(token) + strlen(command) + 2);
		sprintf(fullpath, "%s/%s", token, command);
		if (stat(fullpath, &st) == 0)
		{
			printf(" FOUND\n");
			free(fullpath);
			return (0);
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}

	printf(" NOT FOUND\n");
	return (1);
}

/**
 * main - searches for commands in the system PATH
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	char *path;
	int i;

	/* check for correct usage */
	if (argc < 2)
	{
		printf("Usage: %s filename ...\n", argv[0]);
		return (1);
	}

	/* get the system PATH */
	path = getenv("PATH");
	if (!path)
	{
		fprintf(stderr, "Error: PATH environment variable not set\n");
		return (1);
	}

	/* iterate through each argument */
	i = 1;
	while (argv[i])
	{
		printf("%s:", argv[i]);
		search_path(path, argv[i]);
		i++;
		}

	return (0);
}
