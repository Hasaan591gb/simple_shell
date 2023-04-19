#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int *ptr;
	int n = 5;

	/* Allocate memory for n integers using malloc */
	ptr = (int *)malloc(n * sizeof(int));

	/* Check if memory allocation was successful */
	if (ptr == NULL)
	{
		perror("Error: Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	/* Initialize the allocated memory */
	for (int i = 0; i < n; i++)
	ptr[i] = i + 1;

	/* Print the allocated memory */
	printf("The allocated memory contains: ");
	for (int i = 0; i < n; i++)
		printf("%d ", ptr[i]);
	printf("\n");

	/* Free the allocated memory */
	free(ptr);

	return (0);
}
