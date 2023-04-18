#include <stdio.h>

extern char **environ;

/**
 * main - prints the addresses of the env and environ variables
 * @argc: argument count
 * @argv: argument vector
 * @env: environment array
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	/* Provision for unused variables "argc and argv" */
	(void)argc;
	(void)argv;

	/* print the address of the env variable */
	printf("Address of env: %p\n", (void *)env);

	/* print the address of the environ variable */
	printf("Address of environ: %p\n", (void *)environ);

	return (0);
}
