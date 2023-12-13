#include "shell.h"

/**
 * shell_loop - a shell loop
 * @data: input data
 * @argv: arguments vector
 *
 * Return: 0 if success, 1 if error, or an error
 */

int shell_loop(shell_t *data, char **argv)
{
	ssize_t i = 0;
	int res = 0;

	while (i != -1 && res != -2)
	{
		data->args = NULL;
		data->argv = NULL;
		data->path = NULL;
		data->argc = 0;

		if (isatty(STDIN_FILENO) && data->readfd <= 2)
			print_string("$ ");
		print_char_err(-1);
		i = get_command(data);
		if (i != -1)
		{
			init_data(data, argv);
			res = get_builtin(data);
			if (res == -1)
				check_cmd(data);
		}
		else if (isatty(STDIN_FILENO) && data->readfd <= 2)
			print_char('\n');
		free_data(data, 0);
	}
	set_history(data);
	free_data(data, 1);

	if (!(isatty(STDIN_FILENO) && data->readfd <= 2) && data->status)
		exit(data->status);
	if (res == -2)
	{
		if (data->error_num == -1)
			exit(data->status);
		exit(data->error_num);
	}
	return (res);
}

/**
 * read_buffer - reads a buffer
 * @data: input data
 * @buffer: input buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(shell_t *data, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->readfd, buffer, BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
