#include "shell.h"

/**
 * execute_builtins - handles env and exit builtin functions
 * @token: tokenized commands
 * @env: contains values of environ
 */
void execute_builtins(char *token, char **env)
{
	size_t len;

	if (my_strcmp(token, "exit") == 0) /* check if command is "exit" */
	{
		exit(0); /* exit the shell */
	}
	else if (my_strcmp(token, "env") == 0) /* env built-in command */
	{
		while (*env != NULL)
		{
			len = getStringLength(*env);
			write(STDOUT_FILENO, *env, len);
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}
}
