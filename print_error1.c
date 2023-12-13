#include "shell.h"

/**
 * print_d - function prints a decimal
 * @input: input integer
 * @fd: the fd to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = print_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = print_char_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * err_to_i - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string or converted number, -1 on error
 */
int err_to_i(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: nothing
 */
void remove_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

/**
 * check_chain - checks if we should continue chaining
 * @data: input data
 * @buff: the char buffer
 * @idx: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: nothing
 */
void check_chain(shell_t *data, char *buff, size_t *idx, size_t i, size_t len)
{
	size_t j = *idx;

	if (data->cmd_opperators == 2)
	{
		if (data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (data->cmd_opperators == 1)
	{
		if (!data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*idx = j;
}
