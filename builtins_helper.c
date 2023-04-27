#include "shell.h"

/**
 * execute_exit - exit builtin
 * @tokens: tokenized commands
 */
void execute_exit(char **tokens)
{
	int size = 0;
	const char* error_msg;

	while (tokens[size] != NULL) /* count the number of elements in the array */
	{
		size++;
	}
	if (size > 2) /* check if there are too many arguments */
	{
		error_msg = "Error: too many arguments\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
	}
	else if (size == 2) /* check if there is an argument provided */
	{
		exit(atoi(tokens[1])); /* exit shell with provided status */
	}
	else
	{
		exit (0); /* exit the shell without specifying a status */
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
	char *path;
	char *cwd = getcwd(NULL, 0);


	if (tokens[1] == NULL)
		path = getenv("HOME"); /* if no argument is given, use HOME directory */
	else if (my_strcmp(tokens[1], "-") == 0)
	{
		path = getenv("OLDPWD"); /* if argument is "-", use OLDPWD directory */
		if (path == NULL)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n",
			getStringLength("cd: OLDPWD not set\n"));
			return;
		}
	}
	else
		path = tokens[1]; /* use the given path */
	if (cwd == NULL)
	{
		write(STDERR_FILENO, "cd: getcwd failed\n",
		getStringLength("cd: getcwd failed\n"));
		return;
	}
	if (chdir(path) != 0) /* change directory */
	{
		write(STDERR_FILENO, "cd: unable to change directory\n",
		getStringLength("cd: unable to change directory\n"));
		free(cwd);
		return;
	}
	if (setenv("OLDPWD", cwd, 1) != 0) /* set OLDPWD environment variable */
	{
		write(STDERR_FILENO, "cd: failed to set OLDPWD environment variable\n",
		getStringLength("cd: failed to set OLDPWD environment variable\n"));
		free(cwd);
		return;
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) != 0) /* set PWD environment variable */
	{
		write(STDERR_FILENO, "cd: failed to set PWD environment variable\n",
		getStringLength("cd: failed to set PWD environment variable\n"));
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
void shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: invalid arguments\n",
		getStringLength("setenv: invalid arguments\n"));
	}
	else
	{
		if (setenv(args[1], args[2], 1) != 0) /* set environment variable */
		{
			write(STDERR_FILENO, "setenv: failed to set variable\n",
			getStringLength("setenv: failed to set variable\n"));
		}
	}
}

/**
 * shell_unsetenv - cd builtin
 * @args: tokenized commands
 * Return: 0 or 1
 */
/*  Implementation of the unsetenv command */
void shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: invalid arguments\n",
		getStringLength("unsetenv: invalid arguments\n"));
	}
	else
	{
		if (unsetenv(args[1]) != 0) /* unset environment variable */
		{
			write(STDERR_FILENO, "unsetenv: failed to unset variable\n",
			getStringLength("unsetenv: failed to unset variable\n"));
		}
	}
}

