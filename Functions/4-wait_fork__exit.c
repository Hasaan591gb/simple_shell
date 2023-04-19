#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	pid_t pid;
	int status;

	/* Create child process */
	pid = fork();
	if (pid == -1)
	{
		printf("Failed to create child process\n");
		return (1);
	}

	if (pid == 0)
	{
		/* Child process */
		printf("Child process\n");
		_exit(0);
	}
	else
	{
		/* Parent process */
		printf("Parent process\n");

		/* Wait for child process to terminate */
		if (wait(&status) == -1)
		{
			printf("Failed to wait for child process\n");
			return (1);
		}

		/* Check if child process terminated normally */
		if (WIFEXITED(status))
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
	}

	return (0);
}
