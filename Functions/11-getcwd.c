#include <stdio.h>
#include <unistd.h>

#define MAX_PATH 1024

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char cwd[MAX_PATH];

	/* Get the current working directory */
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working directory: %s\n", cwd);
	else
		perror("Error: getcwd failed");

	return (0);
}
