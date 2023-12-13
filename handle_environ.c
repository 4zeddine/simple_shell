#include "shell.h"

/**
 * get_environ - gets a copy of an array of string of environ
 * @data: input data.
 *
 * Return: Array of strings from environ
 */
char **get_environ(shell_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _getenv - gets the value of an environ variable
 * @data: input data
 * @name: env var name
 *
 * Return: value of environ variable
 */
char *_getenv(shell_t *data, const char *name)
{
	singl_t *node = data->env;
	char *p;

	while (node)
	{
		p = check_start(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - populates env linked list
 * @data: input data
 *
 * Return: 0
 */
int populate_env_list(shell_t *data)
{
	singl_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}

/**
 * _setenv - Initialize or modify a new environment variable or an existing one
 * @data: input data
 * @var: env var string
 * @value: env var value
 *  Return: 0
 */
int _setenv(shell_t *data, char *var, char *value)
{
	char *buffer = NULL;
	singl_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = data->env;
	while (node)
	{
		p = check_start(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @data: input data
 * @var: env var string
 *
 *  Return: 1 if deleted or 0 if not
 */
int _unsetenv(shell_t *data, char *var)
{
	singl_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = check_start(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}
