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
			/* printf("\nStep 1: interactive\n"); */

			write(STDOUT_FILENO, "#cisfun$ ", 9);   /* displays prompt */
		}
		input = read_input(); /* read user input */
		// printf("\nStep 1: get user input\n");
		// printf("\n\tuser input: %s\n", input);
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
		// printf("\nStep 2: tokenize input\n");
		// print_string_array(tokens);
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

/* execute function creates a child process using fork() and executes the user command using execve() */
void execute(char **tokens)
{
	pid_t pid;
	/* char **env = environ; */

	if (my_strcmp(tokens[0], "exit") == 0 || my_strcmp(tokens[0], "env") == 0) /* check if command is built in */
	{
		execute_builtins(tokens[0], environ);
	}
	else
	{
		pid = fork(); /* create child process using fork since we are about to call execve() */
		if (pid == 0) /* fork() is 0 for child process thus pid == 0 if it's a child process */
		{
			// printf("\nStep 3: Check if command exists in PATH directories \n");
			tokens = check_PATH(tokens);
			// printf("\nStep 4: Update your array of tokens");
			// print_string_array(tokens);

			/* print_string_array(tokens); */

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
