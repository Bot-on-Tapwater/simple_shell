#include "shell.h"
/**
 * concatenateStrings - joins two strings together
 * @str1: string concetenated
 * @str2: string joined to str1
 * Return: str1 and str2 combined
 */
char *concatenateStrings(char *str1, char *str2)
{
	int len1 = getStringLength(str1);
	int len2 = getStringLength(str2);
	char *result = malloc(len1 + len2 + 1); /* add one for null terminator */

	if (result == NULL)
	{
		perror("Failed to allocate memory for concatenated string");
		exit(1);
	}
	result = myStrcpy(result, str1);
	result = myStrcat(result, str2);
	return (result);
}

/**
 * myStrcpy - copies contents of one string to another string
 * @dest: copying destination
 * @src: string copied
 * Return: string copied
 */
char *myStrcpy(char *dest, const char *src)
{
	char *originalDest = dest; /* save the original pointer to dest */

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * myStrcat - concatenates two strings
 * @dest: destiation
 * @src: string constant
 * Return: joined string
 */
char *myStrcat(char *dest, const char *src)
{
	char *originalDest = dest;/* save the original pointer to dest */

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * myStrncmp - compares two strings, checks if they are equal
 * @s1: string one compared
 * @s2: string compared with string one
 * @n: compares the first n characters of s1 and s2.
 * Return: 0 on sucess
 */
int myStrncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (*s1 == '\0' || *s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
/**
 * my_strdup - copies the contents of the input string str to the new memory
 * @str: string copied
 * Return: a pointer to the new string.
 */
char *my_strdup(const char *str)
{
	size_t len = getStringLength(str) + 1;
	char *new_str = malloc(len);

	if (new_str == NULL)
		return (NULL);
	memcpy(new_str, str, len);
	return (new_str);
}
