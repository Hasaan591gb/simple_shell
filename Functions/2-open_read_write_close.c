#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	char *file = "test.txt";

	/* Open file */
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open %s\n", file);
		return (1);
	}

	/* Read from file */
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		printf("Failed to read from %s\n", file);
		close(fd);
		return (1);
	}

	/* Write to standard output */
	if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
	{
		printf("Failed to write to standard output\n");
		close(fd);
		return (1);
	}

	/* Close file */
	if (close(fd) == 0)
		printf("Closed %s\n", file);
	else
		printf("Failed to close %s\n", file);

	return (0);
}
