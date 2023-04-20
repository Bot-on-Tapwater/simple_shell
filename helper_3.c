#include "shell.h"

/**
 * my_memcpy - copies bytes from memory
 * @dest: a pointer to the destination buffer
 * @src: a pointer to the source buffer
 * @n: the number of bytes to copy.
 * Return: void pointer to the destination buffer.
 */
void *my_memcpy(void *dest, const void *src, size_t n)
{
	char *pdest = dest;
	const char *psrc = src;
	size_t i;

	for (i = 0; i < n; i++)
	{
		pdest[i] = psrc[i];
	}
	return (dest);
}

/**
 * my_realloc - changes size of memory block
 * @ptr: pointer to the previously allocated memory block
 * @size: new size to allocate
 * Return: a void pointer to the newly allocated memory block.
 */
void *my_realloc(void *ptr, size_t size)
{
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
	{
		return (malloc(size));
	}
	else
	{
		void *new_ptr = malloc(size);

		if (new_ptr == NULL)
		{
			return (NULL);
		}
		my_memcpy(new_ptr, ptr, size);
		free(ptr);
		return (new_ptr);
	}
}

/**
 * printenv -  prints environment variable
 * takes no arguments
 * Return: 0 on success
 */
int printenv(void)
{
	int i = 0;

	while ((environ[i]))
	{
		printString(environ[i]);
		printString("\n");
		i++;
	}

	return (0);
}
