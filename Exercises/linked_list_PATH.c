#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define a node structure for the linked list */
typedef struct node
{
	char *dir; /* directory name */
	struct node *next; /* pointer to the next node */
} node_t;

/**
 * build_path_list - builds a linked list of directories in the system PATH
 *
 * Return: head of the linked list
 */
node_t *build_path_list(void)
{
	node_t *head, *tail, *node;
	char *path, *path_copy, *dir;

	/* get the system PATH */
	path = getenv("PATH");
	if (path == NULL)
	{
		printf("PATH environment variable not found!\n");
		return (NULL);
	}

	/* split the PATH into directories and add them to the linked list */
	head = NULL;
	tail = NULL;
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* create a new node for the directory */
		node = malloc(sizeof(node_t));
		node->dir = strdup(dir);
		node->next = NULL;

		/* add the node to the linked list */
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

/**
 * print_path_list - prints a linked list of directories
 * @head: head of the linked list
 */
void print_path_list(node_t *head)
{
	node_t *node;

	/* iterate through each node and print its directory */
	for (node = head; node != NULL; node = node->next)
		printf("%s\n", node->dir);
}

/**
 * free_path_list - frees a linked list of directories
 * @head: head of the linked list
 */
void free_path_list(node_t *head)
{
	node_t *next_node;

	/* iterate through each node and free its memory */
	while (head != NULL)
	{
		next_node = head->next;
		free(head->dir);
		free(head);
		head = next_node;
	}
}
