#include "shell.h"

/**
 * convert_number - converter number to asci
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array, buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(shell_t *data)
{
	int i;
	singl_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = check_node_start(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(shell_t *data)
{
	int i = 0;
	singl_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
				_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = check_node_start(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
