#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char *dir;
	struct node *next;
} node_t;

node_t *build_path_list(void)
{
	node_t *head, *tail, *node;
	char *path, *path_copy, *dir;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("PATH environment variable not found!\n");
		rerturn (NULL);
	}

	head = NULL;
	tail = NULL;
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		node = malloc(sizeof(node_t));
		node->dir = strdup(dir);
		node->next = NULL;

		if (head == NULL)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (head);
}

void print_path_list(node_t *head)
{
	node_t *node;

	for (node = head; node != NULL; node = node->next)
		printf("%s\n", node->dir);
}

void free_path_list(node_t *head)
{
	node_t *next_node;

	while (head != NULL)
	{
		next_node = head->next;
		free(head->dir);
		free(head);
		head = next_node;
	}
}
