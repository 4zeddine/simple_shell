#include "shell.h"

/**
 * _env - prints the current environment
 * @data: input data
 *
 * Return: 0
 */
int _env(shell_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * _history - prints the history list
 * @data: input data
 *
 *  Return: 0
 */
int _history(shell_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * __exit - exits the shell
 * @data: input data
 *
 *  Return: exits shell with status
 */
int __exit(shell_t *data)
{
	int check_ex;

	if (data->argv[1])
	{
		check_ex = err_to_i(data->argv[1]);
		if (check_ex == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			print_err(data->argv[1]);
			print_char_err('\n');
			return (1);
		}
		data->error_num = err_to_i(data->argv[1]);
		return (-2);
	}
	data->error_num = -1;
	return (-2);
}

/**
 * _help - works like the help buitin
 * @data: input data
 *
 *  Return: 0
 */
int _help(shell_t *data)
{
	char **array;

	array = data->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*array);
	return (0);
}

/**
 * _alias - works like the alias builtin
 * @data: input data
 *
 *  Return: 0
 */
int _alias(shell_t *data)
{
	int i = 0;
	char *p = NULL;
	singl_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _strchr(data->argv[i], '=');
		if (p)
			init_alias(data, data->argv[i]);
		else
			print_alias(check_node_start(data->alias, data->argv[i], '='));
	}

	return (0);
}
