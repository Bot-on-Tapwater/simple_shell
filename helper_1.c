#include "shell.h"


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

/* writes/print string to stdin */
void printString(char *str) 
{
	size_t len = getStringLength(str);
	
	write(STDOUT_FILENO, str, len);
}

/* gets no. of xters in a string */
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

/* writes string to stderr */
void writeStringToStderr(char *str) 
{
	size_t len = getStringLength(str);

	write(STDERR_FILENO, str, len);
}

/* compares two strings to determine if they are equal */
int my_strcmp(const char *str1, const char *str2) 
{
    while (*str1 && *str2 && *str1 == *str2) 
    {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}