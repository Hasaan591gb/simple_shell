#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Check if standard input is a terminal */
	if (isatty(STDIN_FILENO))
		printf("Standard input is a terminal\n");
	else
		printf("Standard input is not a terminal\n");

	/* Check if standard output is a terminal */
	if (isatty(STDOUT_FILENO))
		printf("Standard output is a terminal\n");
	else
		printf("Standard output is not a terminal\n");

	return (0);
}
