#include "shell.h"

/**
 * read_input - read_input function reads user input from stdin using getline()
 * Return: Returns input from stdout
 */
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


