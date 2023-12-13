#include "shell.h"

/**
 * _cd - changes the current directory of the process
 * @data: input data
 *
 *  Return: 0
 */

int _cd(shell_t *data)
{
	char *s, *dir, buffer[BUFF_SIZE];
	int res;

	s = getcwd(buffer, BUFF_SIZE);
	if (!s)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			res = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			res = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			print_string(s);
			print_char('\n');
			return (1);
		}
	print_string(_getenv(data, "OLDPWD="));
	print_char('\n');
	res = chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		res = chdir(data->argv[1]);
	if (res == -1)
	{
		print_error(data, "can't cd to ");
		print_err(data->argv[1]);
		print_char_err('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
