#include <stdio.h>

/**
 * main - prints all arguments it receives
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int i;
	/* Provision for unused variable "argc" */
	(void)ac;

	/* iterate through each argument and print it */
	for (i = 0; *(av + i); i++)
		printf("%s\n", *(av + i));

	return (0);
}
