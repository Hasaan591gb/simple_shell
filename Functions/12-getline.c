#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	/* Print a message */
	printf("Enter a line of text: ");

	/* Read a line of text from standard input */
	nread = getline(&line, &len, stdin);

	/* Check if getline was successful */
	if (nread == -1)
		perror("Error: getline failed");
	else
		printf("You entered: %s", line);

	/* Free the allocated memory */
	free(line);

	return (0);
}
