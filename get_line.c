#include "shell.h"

/**
 * _getline - gets the input line from STDIN
 * @data: input data
 * @ptr: pointer to buffer
 * @size: size of the buffer if not NULL
 *
 * Return: m
 */

int _getline(shell_t *data, char **ptr, size_t *size)
{
	static char buf[BUFF_SIZE];
	static size_t i, len;
	size_t n;
	ssize_t res = 0, m = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		m = *size;
	if (i == len)
		i = len = 0;

	res = read_buffer(data, buf, &len);
	if (res == -1 || (res == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	if (c)
		n = 1 + (unsigned int)(c - buf);
	else
		n = len;

	if (m)
		new_p = _realloc(p, m, m + n);
	else
		new_p = _realloc(p, m, n + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (m)
		_strncat(new_p, buf + i, n - i);
	else
		_strncpy(new_p, buf + i, n - i + 1);
	m += n - i;
	i = n;
	p = new_p;
	if (size)
		*size = m;
	*ptr = p;
	return (m);
}
