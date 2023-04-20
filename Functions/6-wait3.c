#include <stdio.h>
#include <sys/wait.h>
#include <sys/resource.h>
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
	struct rusage rusage;

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
		/* Wait for any child process to terminate and get resource usage */
		if (wait3(&status, 0, &rusage) == -1)
		{
			printf("Failed to wait for child process\n");
			return (1);
		}

		/* Check if child process terminated normally */
		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
			printf("User CPU time used: %ld.%06ld seconds\n",
					rusage.ru_utime.tv_sec, rusage.ru_utime.tv_usec);
			printf("System CPU time used: %ld.%06ld seconds\n",
					rusage.ru_stime.tv_sec, rusage.ru_stime.tv_usec);
		}
	}

	return (0);
}
