#include "shell.h"

/**
 * execute_exit - exit builtin
 * @tokens: tokenized commands
 */
void execute_exit(char **tokens)
{
	int size = 0;
	const char *error_msg;

	while (tokens[size] != NULL) /* count the number of elements in the array */
	{
		size++;
	}
	if (size > 2) /* check if there are too many arguments */
	{
		error_msg = "Error: too many arguments\n";
		write(STDERR_FILENO, error_msg, getStringLength(error_msg));
	}
	else if (size == 2) /* check if there is an argument provided */
	{
		exit(atoi(tokens[1])); /* exit shell with provided status */
	}
	else
	{
		exit(0); /* exit the shell without specifying a status */
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
 * Return: 0
 */
int execute_cd(char **tokens)
{
	char *folder_new = getcwd(NULL, 0);
	char *folder_prev = _getenv("OLDPWD");

	if (tokens[1] == NULL)
	{
		if (chdir(_getenv("HOME")) != 0)
		{
			perror("cd");
		}
	}
	else if (my_strcmp(tokens[1], "-") == 0)
	{
		if (folder_prev == NULL)
			perror("cd: OLDPWD not set\n");
		else
		{
			if (chdir(folder_prev) != 0)
			{
				perror("cd");
			}
			write(STDERR_FILENO, folder_prev, getStringLength(folder_prev));
			write(STDERR_FILENO, "\n", 1);
		}
	}
	else
	{
		if (chdir(tokens[1]) != 0)
		{
			perror("cd");
		}
	}
	if (folder_new == NULL)
	{
		perror("getcwd failed");
	}
	custom_setenv("OLDPWD", _getenv("PWD"), 1);
	custom_setenv("PWD", folder_new, 1);
	free(folder_new);
	return (1);
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

