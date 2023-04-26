#include "shell.h"

/**
 * custom_setenv - clone of setenv
 * @name: variable name
 * @value: new variable value
 * @overwrite: checks if variable exists or not
 * Return: 0 or -1
 */
int custom_setenv(const char *name, const char *value, int overwrite)
{
	int result;
	char *envstr;

	envstr = (char *)malloc(getStringLength(name) + getStringLength(value) + 2);
	if (!envstr)
	{
		return (-1);  /* error, could not allocate memory */
	}

	myStrcpy(envstr, name);
	myStrcat(envstr, "=");
	myStrcat(envstr, value);

	if (_getenv(name))
	{
		if (overwrite)
		{
			result = custom_putenv(envstr);
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		result = custom_putenv(envstr);
	}

	if (result != 0)
	{
		free(envstr);
	}

	return (result);
}

/**
 * custom_unsetenv - clone of setenv
 * @name: variable name
 * Return: 0 or -1
 */
int custom_unsetenv(const char *name)
{
	int i, j, len;
	char **envp, **newenvp;

	if (!name || !*name)
	{
		return (-1);  /* error, invalid argument */
	}

	envp = environ;

	if (!envp || !*envp)
	{
		return (-1);  /* error, environment not available */
	}

	len = getStringLength(name);

	newenvp = (char **)malloc(sizeof(char *) * (custom_environSize() + 1));
	if (!newenvp)
	{
		return (-1);  /* error, could not allocate memory */
	}

	for (i = 0, j = 0; envp[i]; i++)
	{
		if (myStrncmp(envp[i], name, len) != 0 || envp[i][len] != '=')
		{
			newenvp[j++] = envp[i];
		}
	}

	newenvp[j] = NULL;

	environ = newenvp;

	return (0);
}

