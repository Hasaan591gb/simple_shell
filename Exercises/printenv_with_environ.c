#include <stdio.h>

extern char **environ;

/**
 * main - prints the environment variables
 *
 * Return: 0 on success
 */
int main(void)
{
	char **env;

	/* iterate through each environment variable and print it */
	for (env = environ; *env != NULL; env++)
		printf("%s", *env);

	return (0);
}
