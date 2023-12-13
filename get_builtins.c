#include "shell.h"

/**
 * get_builtin - get the builtin command
 * @data: input data
 *
 * Return: -1 if not found, 0 if executed, 1 if found but not successful,
 * -2 if signals exit()
 */
int get_builtin(shell_t *data)
{
	int i = 0, res;
	builtins_t builtins[] = {
		{"exit", __exit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};
	res = -1;

	while  (builtins[i].flag)
	{
		if (_strcmp(data->argv[0], builtins[i].flag) == 0)
		{
			data->line_count++;
			res = builtins[i].func(data);
			break;
		}
		i++;
	}

	return (res);
}
