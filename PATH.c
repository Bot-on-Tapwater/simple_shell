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
	char *path = _getenv("PATH");
	char *path_copy = my_strdup(path);
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

		node->str = my_strdup(token);
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
	int command_len = getStringLength(command);
	int path_len;
	int new_len;
	char *new_path;

	while (path_list != NULL)
	{
		path = path_list->str;
		path_len = getStringLength(path);
		new_len = path_len + command_len + 2; /* +2 for the "/" and the '\0'*/
		new_path = malloc(new_len * sizeof(char));
		if (new_path == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		myStrcpy(new_path, path);
		myStrcat(new_path, "/");
		myStrcat(new_path, command);
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
/**
 * _getenv - gets the value stored in specified variable name
 * @name: Variable name
 * Return: values stored in the variable
 */
char *_getenv(const char *name)
{
	int i, len; /* i is used to traverse environ global variable */
	char *env_val; /* string to store value of variable name e.g PATH="env_val" */

	len = getStringLength(name); /* length of variable name e.g ("PATH" = 4)*/

	for (i = 0; environ[i] != NULL; i++)
	{
		if (myStrncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		/* if match found */
		{
			env_val = &environ[i][len + 1];
		/* store value string  in env_val variable */
			return (env_val);
		}
	}

	return (NULL);
}
