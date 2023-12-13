#include "shell.h"

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: size of previous block
 * @new_size: size of new block
 *
 * Return: pointer to new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *tmp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	tmp = malloc(new_size);
	if (!tmp)
		return (NULL);

	if (old_size < new_size)
	{
		old_size = old_size;
	}
	else
	{
		old_size = new_size;
	}
	while (old_size--)
		tmp[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (tmp);
}

/**
 **_memset - set memory with a constant byte
 *@str: pointer to the memory area
 *@pos: byte to fill *str with
 *@num: amount of bytes to be filled
 *Return: pointer to the memory area str
 */
char *_memset(char *str, char pos, unsigned int num)
{
	unsigned int i = 0;

	while (i < num)
	{
		str[i] = pos;
		i++;
	}
	return (str);
}
