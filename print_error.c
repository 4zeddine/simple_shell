#include "shell.h"

/**
 * print_err - prints an error string
 * @str: input string
 *
 * Return: Nothing
 */
void print_err(char *str)
{
	int i;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		print_char_err(str[i]);
	}
}

/**
 * print_char_err - prints the character c
 * @c: The character to print
 *
 * Return: if successful 1 or -1 if error.
 */
int print_char_err(char c)
{
	static int i;
	static char buffer[BUFF_SIZE];

	if (c == -1 || i >= BUFF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}

	if (c != -1)
	{
		buffer[i] = c;
		i++;
	}

	return (1);
}

/**
 * print_fd - prints the character c to given fd
 * @c: The character to print
 * @fd: The fd to write to
 *
 * Return: if successful 1 or -1 if error.
 */
int print_fd(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * print_string_sfd - prints an input string
 * @str: the string to be printed
 * @fd: the fd to write to
 *
 * Return: the number of chars printed
 */
int print_string_sfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += print_fd(*str++, fd);
	}
	return (i);
}

/**
 * print_error - prints an error message
 * @data: the parameter & return info struct
 * @str_e: string containing specified error type
 * Return: 0 if no numbers in string or the converted number, -1 on error.
 */
void print_error(shell_t *data, char *str_e)
{
	print_err(data->fname);
	print_err(": ");
	print_d(data->line_count, STDERR_FILENO);
	print_err(": ");
	print_err(data->argv[0]);
	print_err(": ");
	print_err(str_e);
}
