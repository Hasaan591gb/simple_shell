#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	pid_t my_pid;

	/* Get the process ID */
	my_pid = getpid();
	printf("My process ID: %d\n", my_pid);

	/* Send a SIGTERM signal to the current process */
	if (kill(my_pid, SIGTERM) == -1)
		perror("Error: kill failed");

	return (0);
}
