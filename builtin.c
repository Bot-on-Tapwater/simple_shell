#include "shell.h"

/**
 * execute_builtins - handles env and exit builtin functions
 * @token: tokenized commands
 * @env: contains values of environ
 */
void execute_builtins(char **tokens, char **env)
{
	size_t len;
	char *cwd;

	if (my_strcmp(tokens[0], "exit") == 0) /* check if command is "exit" */
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
	else if (my_strcmp(tokens[0], "env") == 0) /* env built-in command */
	{
		while (*env != NULL)
		{
			len = getStringLength(*env);
			write(STDOUT_FILENO, *env, len);
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}

	else if (my_strcmp(tokens[0], "cd") == 0) /* cd built-in command */
	{
		char *path;
		if (tokens[1] == NULL)
		{
			path = _getenv("HOME"); /* if no argument is given, use HOME directory */
		}
		else if (my_strcmp(tokens[1], "-") == 0)
		{
			path = _getenv("OLDPWD"); /* if argument is "-", use OLDPWD directory */
			if (path == NULL)
			{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", getStringLength("cd: OLDPWD not set\n"));
			return;
			}
		}
		else
		{
			path = tokens[1]; /* use the given path */
		}
		
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			write(STDERR_FILENO, "cd: getcwd failed\n", getStringLength("cd: getcwd failed\n"));
			return;
		}
		if (chdir(path) != 0) /* change directory */
		{
			write(STDERR_FILENO, "cd: unable to change directory\n", getStringLength("cd: unable to change directory\n"));
			free(cwd);
			return;
		}
		if (setenv("OLDPWD", cwd, 1) != 0) /* set OLDPWD environment variable */
		{
			write(STDERR_FILENO, "cd: failed to set OLDPWD environment variable\n", getStringLength("cd: failed to set OLDPWD environment variable\n"));
			free(cwd);
			return;
		}
		if (setenv("PWD", getcwd(NULL, 0), 1) != 0) /* set PWD environment variable */
		{
			write(STDERR_FILENO, "cd: failed to set PWD environment variable\n", getStringLength("cd: failed to set PWD environment variable\n"));
			free(cwd);
			return;
		}
		free(cwd);
	}

	else if (my_strcmp(tokens[0], "setenv") == 0) /* env built-in command */
	{
		printf("setenv not implemented\n");
	}
	
	else if (my_strcmp(tokens[0], "unsetenv") == 0) /* env built-in command */
	{
		printf("unsetenv not implemented\n");
	}
}
