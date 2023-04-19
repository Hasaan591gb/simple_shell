#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	struct stat sb;
	int ret;

	/* Create a symbolic link */
	symlink("test.txt", "test_link");

	/* Call lstat on the symbolic link */
	ret = lstat("test_link", &sb);

	/* Check for errors */
	if (ret == -1)
	{
		perror("lstat");
		return (1);
	}

	/* Check if the file is a symbolic link */
	if (S_ISLNK(sb.st_mode))
		printf("test_link is a symbolic link\n");

	/* Call stat on the symbolic link */
	ret = stat("test_link", &sb);

	/* Check for errors */
	if (ret == -1)
	{
		perror("stat");
		return (1);
	}

	/* Check if the file is a regular file */
	if (S_ISREG(sb.st_mode))
		printf("test_link points to a regular file\n");

	return (0);
}
