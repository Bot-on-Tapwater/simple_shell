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
		free(input);
		return (NULL); /* end of file */
	}
	return (input);
}

/**
 * printString - writes/print string to stdin
 * @str: string written
 */
void printString(char *str)
{
	size_t len = getStringLength(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * getStringLength -  gets no. of characters in a string
 * @str: string whose length is calculated
 * Return: Length of string
 */
int getStringLength(const char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * writeStringToStderr - writes string to stderr
 * @str: Error message printed
 */
void writeStringToStderr(char *str)
{
	size_t len = getStringLength(str);

	write(STDERR_FILENO, str, len);
}

/**
 * my_strcmp - compares two strings to determine if they are equal
 * @str1: the string compared
 * @str2: the second string compared
 * Return: the diff btwn the ASCII values of the characters pointed by str
 */
int my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
