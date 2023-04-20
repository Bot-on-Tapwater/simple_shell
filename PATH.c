#include "shell.h"

char** check_PATH(char **args)
{
	int i = 0; /* traverse array of PATH directories */
	char **path = get_path_directories(); /* array of PATH directories */

	/* print_string_array(path); */

	while (path[i] != NULL) /* check if we have run out of PATH directories */
	{
		char *command_path; /* stores full PATH to shell commands */		

		if (access(args[0], X_OK) == 0) /* check if command entered is full PATH or shorthand version (ls OR /bin/ls)*/
		{
			/* if full PATH, proceed to execute with execve */
			return (args);
		}

		command_path = concatenateStrings(concatenateStrings(path[i], "/"), args[0]);

		if (access(command_path, X_OK) == 0) /* check if command exists */
		{
			// printf("\n\tcommand: %s, exists in %s directory as: %s\n", args[0], path[i], command_path);
			args[0] = command_path;
			return (args);
		}	
		i++;
	}
	writeStringToStderr(concatenateStrings(args[0], ": command not found\n"));
	return (0);
}


/* gets the value stored in specified variable name */
char *_getenv(const char *name)
{
	int i, len; /* i is used to traverse environ global variable */
	char *env_val; /* string to store value of variable name e.g PATH="env_val" */

	len = getStringLength(name); /* length of variable name e.g ("PATH" = 4)*/

	for (i = 0; environ[i] != NULL; i++)
	{
		if (myStrncmp(name, environ[i], len) == 0 && environ[i][len] == '=') /* if match found */
		{
			env_val = &environ[i][len + 1]; /* store value string  in env_val variable */
			return (env_val);
		}
	}

	return (NULL);
}

/* gets a list of directories in PATH variable */
char **get_path_directories(void)
{
	char *path_var = _getenv("PATH"); /* stores a string of PATH directories separated by ":" */
	char **path = NULL; /* array of PATH directories */
	char *dir; /* temp store for strings/tokens */
	int i = 0; /* traverse through path (array of path directories) */

	if (path_var == NULL) /* check if PATH variable was obtained */
	{
		writeStringToStderr("PATH variable not set\n");
		exit(EXIT_FAILURE);
	}

	path = malloc((MAX_PATH + 1) * sizeof(char *)); /* allocate memory for path array */

	dir = strtok(path_var, ":"); /* get first token/string */

	while (dir != NULL && i < MAX_PATH) 
	{
		path[i++] = dir; /* populate array of path directories */
		dir = strtok(NULL, ":"); /* get subsequent path directories */
	}
	path[i] = NULL; /* add terminating NULL pointer */

	return (path);
}



