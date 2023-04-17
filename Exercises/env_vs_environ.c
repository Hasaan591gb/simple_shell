#include <stdio.h>

extern char **environ;

int main(int argc, char **argv, char **env)
{
	printf("Address of env: %p\n", (void *)env);
	printf("Address of environ: %p\n", (void *)environ);

	return (0);
}
