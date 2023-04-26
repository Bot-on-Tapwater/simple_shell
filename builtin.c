#include "shell.h"

/**
 * execute_builtins - handles env and exit builtin functions
 * @tokens: tokenized commands
 * @env: contains values of environ
 */
void execute_builtins(char **tokens, char **env)
{
	if (strcmp(tokens[0], "exit") == 0) /* check if command is "exit" */
	{
		execute_exit(tokens);
	}
	else if (strcmp(tokens[0], "env") == 0) /* env built-in command */
	{
		execute_env(env);
	}
}

