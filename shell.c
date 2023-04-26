#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024     /* IGNORE FOR NOW */
#define MAX_TOKEN_SIZE 64       /* IGNORE FOR NOW */
#define MAX_NUM_TOKENS 64       /* max number of whitespace/" " separated strings a user can enter */

extern char **environ;

/* function declarations */
char *read_input();
int tokenize(char *input, char **tokens, int max_tokens);
void execute(char **tokens);

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
		num_tokens = tokenize(input, tokens, MAX_NUM_TOKENS); /* tokenize user input */
		if (num_tokens > 0) /* only true if at least one string is entered */
		{
			execute(tokens); /* execute user command */
		}
		free(input); /* free resources */
	}
	return (0);
}

/* read_input function reads user input from stdin using getline() function */
char *read_input()
{
	char *input = NULL;
	size_t input_size = 0;
	if (getline(&input, &input_size, stdin) == -1)
	{
		return (NULL); /* end of file */
	}
	return (input);
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

/* execute function creates a child process using fork() and executes the user command using execve() */
void execute(char **tokens)
{
	pid_t pid;
	char **env = environ;
	size_t len;
	
	if (strcmp(tokens[0], "exit") == 0) /* check if command is "exit" */
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
	else if 
		(strcmp(tokens[0], "env") == 0) /* env built-in command */
		{
			while (*env != NULL)
			{
				len = strlen(*env);
				write(STDOUT_FILENO, *env, len);
				write(STDOUT_FILENO, "\n", 1);
				env++;
			}
		}
	else if 
		(strcmp(tokens[0], "setenv") == 0) /* setenv built-in command */
		{
			if (tokens[1] == NULL || tokens[2] == NULL)
			{
				write(STDERR_FILENO, "setenv: invalid arguments\n", strlen("setenv: invalid arguments\n"));
			}
			else
			{
				if (setenv(tokens[1], tokens[2], 1) != 0) /* set environment variable */
				{
					write(STDERR_FILENO, "setenv: failed to set variable\n", strlen("setenv: failed to set variable\n"));
				}
			}
		}
	else if (strcmp(tokens[0], "unsetenv") == 0) /* unsetenv built-in command */
	{
		if (tokens[1] == NULL)
		{
			write(STDERR_FILENO, "unsetenv: invalid arguments\n", strlen("unsetenv: invalid arguments\n"));
		}
		else
		{
			if (unsetenv(tokens[1]) != 0) /* unset environment variable */
			{
				write(STDERR_FILENO, "unsetenv: failed to unset variable\n", strlen("unsetenv: failed to unset variable\n"));
			}
		}
	}
	else
	{
		pid = fork(); /* create child process using fork since we are about to call execve() */
		if (pid == 0) /* fork() is 0 for child process thus pid == 0 if it's a child process */
		{
			execve(tokens[0], tokens, environ); /* execute commands using execve() */
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
}
