#include "shell.h"

/**
 * init_alias - initialise alias with a string
 * @data: input data
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int init_alias(shell_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * unset_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: 0 if successful, 1 if not.
 */
int unset_alias(shell_t *data, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, check_node_start(data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 if successful, 1 if not.
 */
int print_alias(singl_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			print_char(*a);
		print_char('\'');
		print_string(p + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}
