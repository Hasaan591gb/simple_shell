#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
	pid_t my_pid;
	char *token;
	char *path = "/bin/ls";
	char *args[] = {path, "-l", ".", NULL};
	struct stat st;

	/* Get the process ID */
	my_pid = getpid();
	printf("My process ID: %d\n", my_pid);

	/* Use stat to check if the file exists */
	if (stat(path, &st) == 0)
		printf("%s exists\n", path);
	else
		printf("%s does not exist\n", path);

	/* Use strtok to split a string */
	token = strtok(path, "/");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, "/");
	}

	/* Use execve to execute a command */
	if (execve(path, args, NULL) == -1)
		perror("Error: execve failed");

	return (0);
}
