#include "shell.h"

/* function declarations */

int main(void)
{
	char *input = NULL;         /* buffer to store user input */
	char *tokens[MAX_NUM_TOKENS];   /* array of tokens/strings */
	int num_tokens;

	while (1)
	{
		if (isatty(0))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);   /* displays prompt */
		}
		input = read_input(); /* read user input */
		if (input == NULL) /* end of file */
		{
			if (isatty(0))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			free(input);
			exit(0);
		}
		num_tokens = tokenize(input, tokens, MAX_NUM_TOKENS);
		if (num_tokens > 0) /* only true if at least one string is entered */
		{
			execute(tokens); /* execute user command */
		}
		free(input); /* free resources */
	}
	return (0);
}

/* tokenize function breaks a string into tokens using strtok() function */
int tokenize(char *input, char **tokens, int max_tokens)
{
	int num_tokens = 0;
	char *token = strtok(input, " \n"); /* get first token/string */

	while (token != NULL && num_tokens < max_tokens)
	{
		tokens[num_tokens] = token; /* populate "tokens" array with strings */
		num_tokens++; /* move to next index in "tokens" array */
		token = strtok(NULL, " \n"); /* gets subsequent tokens/strings */
	}
	tokens[num_tokens] = NULL; /* tokens array has to end with NULL, because of execve() function */
	return (num_tokens); /* number of tokens/strings */
}

/* checks whether the command is a built in or located in PATH */
char* command_checker(char **tokens)
{
	char *path;
	LL *pathLL;
	char *builtins[6] = {"exit", "env", "cd", "unsetenv", "setenv", NULL};
	int i;	
		
	for(i = 0; builtins[i]; i++)
	{
		if (my_strcmp(tokens[0], builtins[i]) == 0)
		{
			execute_builtins(tokens, environ);
			return (NULL);	
		}
	}

	if (access(tokens[0], X_OK) == 0) /* check if command entered is full PATH or shorthand version (ls OR /bin/ls)*/
	{
		/* if full PATH, proceed to execute with execve */
		path = tokens[0];
		return (path);
	}
	else if (access(tokens[0], X_OK) != 0)
	{
		pathLL = path_list();
		path = find_executable(tokens[0], pathLL);

		if (path == NULL)
		{
			writeStringToStderr(concatenateStrings(tokens[0], ": command not found\n"));
		}
		return (path);
	}

}

/* execute function creates a child process using fork() and executes the user command using execve() */
void execute(char **tokens)
{
	pid_t pid;
	char *path = command_checker(tokens);

	if (path == NULL)
	{
		return;
	}

	pid = fork(); /* create child process using fork since we are about to call execve() */
	if (pid == 0) /* fork() is 0 for child process thus pid == 0 if it's a child process */
	{
		execve(path, tokens, environ); /* execute commands using execve() */
		perror("execve failure"); /* only execeutes if execve fails */
		exit(1); /* only execeutes if execve fails */
	}
	else if (pid > 0) /* fork() is > 0 for parent process thus pid > 0 */
	{
		wait(NULL); /* since it's parent process, ask it to wait for child process to complete using wait */
	}
	else /* only true if fork() fails pid == -1 */
	{
		perror("fork failed");
		exit(1);
	}
}
