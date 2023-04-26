#include "shell.h"
/**
 * free_list - frees linked list
 * @head: a pointer to the head node of the list
 */
void free_list(LL *head)
{
	LL *temp;

	while (head != NULL)
	{
		temp = head; /* store current head */
		head = head->next; /* move to next node */
		free(temp->str); /* free string */
		free(temp); /* free node */
	}
}
/**
 * add_node - adds a new node to the list
 * @head_ref: a double pointer to the head node
 * @str: string stored on the new node
 */
void add_node(LL **head_ref, char *str)
{
	LL *new_node = (LL *)malloc(sizeof(LL)); /* allocate memory for new node */

	new_node->str = str; /* assign string to new node */
	new_node->next = *head_ref; /* make the new node point to the current head */
	*head_ref = new_node; /* make the new node the new head */
}
/**
 * path_list - finds the path in env variable
 * Return: head node to the linked list
 */
LL *path_list(void)
{
	LL *head = NULL;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	LL *node;
	char *token;

	if (!path_copy)
	{
		perror("malloc failure");
		return (NULL);
	}
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		node = malloc(sizeof(LL));
		if (!node)
		{
			perror("malloc failure");
			free_list(head);
			free(path_copy);
			return (NULL);
		}

		node->str = strdup(token);
		node->next = head;
		head = node;

		token = strtok(NULL, ":");
	}
	free(path_copy);

	return (head);
}
/**
 * find_executable - checks if the file exists and is executable
 * @command: command being executed
 * @path_list: list of directories to check command
 * Return: executable path for the command
 */
char *find_executable(char *command, LL *path_list)
{
	char *executable_path = NULL;
	char *path = NULL;
	int command_len = strlen(command);
	int path_len;
	int new_len;
	char *new_path;

	while (path_list != NULL)
	{
		path = path_list->str;
		path_len = strlen(path);
		new_len = path_len + command_len + 2; /* +2 for the "/" and the '\0'*/
		new_path = malloc(new_len * sizeof(char));
		if (new_path == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		strcpy(new_path, path);
		strcat(new_path, "/");
		strcat(new_path, command);
		if (access(new_path, X_OK) == 0) /*check if file exists and executable*/
		{
			executable_path = new_path;
		break;
		}
		free(new_path); /* the file does not exist, so we free the memory */
		path_list = path_list->next;
	}
	return (executable_path);
}
