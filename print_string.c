#include "shell.h"

/**
 *print_string - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
		print_char(str[i]);
}

/**
 * print_char - writes the character c to stdout
 * @l: The character to print
 *
 * Return: if successful 1, or -1 if error.
 */
int print_char(char l)
{
	static int i;
	static char buffer[BUFF_SIZE];

	if (l == -1 || i >= BUFF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (l != -1)
	{
		buffer[i] = l;
		i++;
	}
	return (1);
}
