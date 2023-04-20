#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/**
 * sigint_handler - Handler for the SIGINT signal
 * @signum: Signal number
 */
void sigint_handler(int signum)
{
	(void)signum;
	printf("\nCaught SIGINT, exiting...\n");
	_exit(0);
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Install a signal handler for SIGINT */
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("Error: signal failed");

	/* Print a message */
	printf("Press Ctrl-C to exit\n");

	/* Loop forever */
	while (1)
		pause();

	return (0);
}
