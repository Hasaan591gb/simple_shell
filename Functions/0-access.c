#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *file = "test.txt";

	/* Check if file exists */
	if (access(file, F_OK) != -1)
		printf("%s exists\n", file);
	else
		printf("%s does not exist\n", file);

	/* Check if file is readable */
	if (access(file, R_OK) != -1)
		printf("%s is readable\n", file);
	else
		printf("%s is not readable\n", file);

	/* Check if file is writable */
	if (access(file, W_OK) != -1)
		printf("%s is writable\n", file);
	else
		printf("%s is not writable\n", file);

	/* Check if file is executable */
	if (access(file, X_OK) != -1)
		printf("%s is executable\n", file);
	else
		printf("%s is not executable\n", file);

	/* Check if file exists and is readable, writable, and executable */
	if (access(file, F_OK | R_OK | W_OK | X_OK) != -1)
		printf("%s exists and is readable, writable, and executable\n", file);
	else
		printf("%s does not exist or is not readable,
				writable, or executable\n", file);

	return (0);
}
