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
 * @tokens: tokenized commands
 * @env: environment variable
 */
void execute_env(char **env)
{
	while (*env != NULL)
	{
		size_t len;

		len = getStringLength(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * execute_cd - cd builtin
 * @tokens: tokenized commands
 */
void execute_cd(char **tokens)
{
	char *cwd, *path;

	if (tokens[1] == NULL)
		path = _getenv("HOME"); /* if no argument is given, use HOME directory */
	else if (my_strcmp(tokens[1], "-") == 0)
	{
		path = _getenv("OLDPWD"); /* if argument is "-", use OLDPWD directory */
		if (path == NULL)
		{
			writeStringToStderr("cd: OLDPWD not set\n");
			return;
		}
	}
	else
		path = tokens[1]; /* use the given path */
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		writeStringToStderr("cd: getcwd failed\n");
		return;
	}
	if (chdir(path) != 0) /* change directory */
	{
		writeStringToStderr("cd: unable to change directory\n");
		free(cwd);
		return;
	}
	if (setenv("OLDPWD", cwd, 1) != 0) /* set OLDPWD environment variable */
	{
		writeStringToStderr("cd: failed to set OLDPWD environment variable\n");
		free(cwd);
		return;
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) != 0) /* set PWD environment variable */
	{
		writeStringToStderr("cd: failed to set PWD environment variable\n");
		free(cwd);
		return;
	}
	free(cwd);
}

/**
 * shell_setenv - setenv builtin
 * @args: tokenized commands
 * Return: 0 or 1
 */
/* Implementation of the setenv command */
int shell_setenv(char **args)
{
	if (args[1] == NULL)
	{
		/* If no arguments are provided, print an error message and return failure */
		writeStringToStderr("setenv: Too few arguments\n");
		return (1);
	}
	else if (args[2] == NULL)
	{
		/* If only one argument is provided, use an empty string as the value */
		custom_setenv(args[1], "", 1);
		return (0);
	}
	else
	{
		custom_setenv(args[1], args[2], 1);
		return (0);
	}
}

/**
 * shell_unsetenv - cd builtin
 * @args: tokenized commands
 * Return: 0 or 1
 */
/*  Implementation of the unsetenv command */
int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		/* If no arguments are provided, print an error message and return failure */
		writeStringToStderr("setenv: Too few arguments\n");
		return (1);
	}
	else
	{
		custom_unsetenv(args[1]);
		return (0);
	}
}
