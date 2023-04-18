#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the current and parent process IDs
 *
 * Return: 0 on success
 */
int main(void)
{
	pid_t pid, ppid;

	/* get and print the current process ID */
	pid = getpid();
	printf("Current process ID: %d\n", pid);

	/* get and print the parent process ID */
	ppid = getppid();
	printf("Parent process ID: %d\n", ppid);

	return (0);
}
