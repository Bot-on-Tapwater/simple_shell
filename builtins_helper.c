#include "shell.h"

/**
 * execute_exit - exit builtin
 * @tokens: tokenized commands
 */
void execute_exit(char **tokens)
{
	if (tokens[1] != NULL) /* check if there is an argument provided */
	{
		int status = atoi(tokens[1]); /* convert argument to integer */

		exit(status); /* exit shell with provided status */
	}
	else
	{
		exit(0); /* exit the shell with default status 0 */
	}
}

/**
 * execute_env - env builtin
 * @env: environment variable
 */
void execute_env(char **env)
{
	while (*env != NULL)
	{
		size_t len;

		len = strlen(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
