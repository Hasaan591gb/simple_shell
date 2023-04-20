#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	time_t start, end;
	double elapsed;

	/* Get the current time */
	time(&start);

	/* Print a message without a newline */
	printf("Sleeping for 5 seconds...");
	fflush(stdout);

	/* Sleep for 5 seconds */
	sleep(5);

	/* Get the current time */
	time(&end);

	/* Calculate the elapsed time */
	elapsed = difftime(end, start);

	/* Print the elapsed time */
	printf("\nElapsed time: %.2f seconds\n", elapsed);

	return (0);
}
