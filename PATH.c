#include "shell.h"

extern char **environ; /* global environment variable */

/* extract tokens from user input string */
char **parse_input(char *line)
{
    	int bufsize = MAX_ARGS; /* memsize for array of strings/tokens */
   	int position = 0; /* tracks index in array of strings/tokens */
    	char **tokens = malloc(bufsize * sizeof(char*)); /* array of strings/tokens */
    	char *token; /* temp store for token/strings */

	if (!tokens) /* malloc check */
	{
		writeStringToStderr("Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS); /* get first token */
	while (token != NULL) /* check if there are any remaining tokens */
	{
		tokens[position] = token; /* populate array of strings/tokens with tokens/strings */
		position++; /* traverse array of strings/tokens */

		if (position >= bufsize) /* if memory exceeded use realloc to expand memeory */
		{
			bufsize += MAX_ARGS;
			tokens = my_realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) /* realloc check */
			{
			writeStringToStderr("Allocation error\n");
			exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS); /* get subsequent tokens/strings */
	}
	tokens[position] = NULL; /* add NULL at end of array of tokens/strings */
	return (tokens);
}

/* execute command if it exists */


char** check_PATH(char **args) 
{
	/* pid_t pid; */ /* to check if parent or child process running */
	/* int status; */ /* stores child process status in waitpid() */
	int i = 0; /* traverse array of PATH directories */
	char **path = get_path_directories(); /* array of PATH directories */

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



