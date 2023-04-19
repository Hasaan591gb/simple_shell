#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	struct stat sb;
	int fd;
	int ret;

	/* Open the file "test.txt" */
	fd = open("test.txt", O_RDONLY);

	/* Check for errors */
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	/* Call fstat on the file descriptor */
	ret = fstat(fd, &sb);

	/* Check for errors */
	if (ret == -1)
	{
		perror("fstat");
		return (1);
	}

	/* Print the size of the file */
	printf("Size: %lld\n", (long long) sb.st_size);

	/* Close the file descriptor */
	close(fd);

	return (0);
}
