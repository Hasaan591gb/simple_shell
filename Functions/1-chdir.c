#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *path = "/tmp";

	/* Change current working directory */
	if (chdir(path) == 0)
		printf("Changed current working directory to %s\n", path);
	else
		printf("Failed to change current working directory to %s\n", path);

	return (0);
}
