#include "shell.h"


alias_node *alias_list = NULL;

/**
 * print_aliases - prints linked list
 */
void print_aliases(void)
{
	alias_node *current = alias_list;
	int len;
	char buffer[1024];

	while (current != NULL)
	{
		len = snprintf(buffer, 1024, "%s='%s'\n", current->name, current->value);
		write(STDOUT_FILENO, buffer, len);
		current = current->next;
	}
}

/**
 * alias_command - logic for alias builtin
 * @args: array of tokens
 */
void alias_command(char **args)
{

	alias_node *current;
	char *equal_sign;
	char *name;
	char *value;
	alias_node *new_alias;
	int i, len;
	char buffer[1024];

	if (args[1] == NULL)
	{
		print_aliases();
		return;
	}

	for (i = 1; args[i] != NULL; i++)
	{
		equal_sign = strchr(args[i], '=');
		if (equal_sign == NULL)
		{
			current = alias_list;
			while (current != NULL)
			{
				if (strcmp(args[i], current->name) == 0)
				{
				len = snprintf(buffer, 1024, "%s='%s'\n", current->name, current->value);
				write(STDOUT_FILENO, buffer, len);
				break;
				}
				current = current->next;
			}
		}
		else
		{
		*equal_sign = '\0';
		name = args[i];
		value = equal_sign + 1;
		current = alias_list;
		while (current != NULL)
		{
			if (strcmp(name, current->name) == 0)
			{
			free(current->value);
			current->value = strdup(value);
			break;
			}
			current = current->next;
		}

		if (current == NULL)
		{
			new_alias = malloc(sizeof(alias_node));
			new_alias->name = strdup(name);
			new_alias->value = strdup(value);
			new_alias->next = alias_list;
			alias_list = new_alias;
		}
		}
	}
}
