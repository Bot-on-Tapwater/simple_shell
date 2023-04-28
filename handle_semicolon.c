#include "shell.h"

/**
 * handle_semicolon - handles ";" separator
 * @input: input string that needs to be tokenized
 */
void handle_semicolon(char *input)
{
	char *commands[MAX_ARGS];
	char *args[MAX_ARGS];
	pid_t pid;
	int j, status;

	delim_tokenize(input, commands, MAX_NUM_TOKENS, ";");

	/* Execute each command in sequence */
	for (j = 0; commands[j] != NULL; j++)
	{
		delim_tokenize(commands[j], args, MAX_NUM_TOKENS, " \t\n");
		if (args[0] != NULL)/*check if arguments are passed*/
		{
			pid = fork();
			if (pid == 0)
			{
				execute(args);
				exit(0);
			}
			else if (pid < 0)
			{
				perror("fork failed");
				exit(1);
			}
			else
			{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			}
		}
	}
}

/**
 * delim_tokenize - breaks a string into tokens using strtok() function
 * @input: input string that needs to be tokenized.
 * @tokens: array that will hold the resulting tokens
 * @max_tokens: max no of tokens that can be extracted from the input string
 * @delim: delimiter string
 * Return: number of tokens
 */
int delim_tokenize(char *input, char **tokens, int max_tokens, char *delim)
{
	int num_tokens = 0;
	char *token = strtok(input, delim); /* get first token/string */

	while (token != NULL && num_tokens < max_tokens)
	{
		tokens[num_tokens] = token; /* populate "tokens" array with strings */
		num_tokens++; /* move to next index in "tokens" array */
		token = strtok(NULL, delim); /* gets subsequent tokens/strings */
	}
	tokens[num_tokens] = NULL; /* tokens array has to end with NULL*/
	/*execve() works with null terminated strings */
	return (num_tokens); /* number of tokens/strings */
}


