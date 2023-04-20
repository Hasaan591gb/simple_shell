#include <stdio.h>
#include <dirent.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	DIR *dir;
	struct dirent *entry;
	char *directory = ".";

	/* Open directory */
	dir = opendir(directory);
	if (dir == NULL)
	{
		printf("Failed to open directory %s\n", directory);
		return (1);
	}

	/* Read from directory */
	while ((entry = readdir(dir)) != NULL)
		printf("%s\n", entry->d_name);

	/* Close directory */
	if (closedir(dir) == 0)
		printf("Closed directory %s\n", directory);
	else
		printf("Failed to close directory %s\n", directory);

	return (0);
}
