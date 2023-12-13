#include "shell.h"

/**
 * _set_env - Initialize or modify a new environment variable
 * @data: input data
 *
 *  Return: Always 0
 */
int _set_env(shell_t *data)
{
	if (data->argc != 3)
	{
		print_err("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_env - Remove an environment variable
 * @data: input data
 *
 *  Return: Always 0
 */
int _unset_env(shell_t *data)
{
	int i;

	if (data->argc == 1)
	{
		print_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return (0);
}
