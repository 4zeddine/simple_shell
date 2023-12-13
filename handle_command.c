#include "shell.h"

/**
 * check_cmd - looks for a command in a path
 * @data: input data
 *
 * Return: nothing
 */
void check_cmd(shell_t *data)
{
	char *path = NULL;
	int i, n;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, n = 0; data->args[i]; i++)
		if (!is_delim(data->args[i], DELIMS))
			n++;
	if (!n)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		exec_cmd(data);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && data->readfd <= 2) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			exec_cmd(data);
		else if (*(data->args) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}


/**
 * exec_cmd - executs a command
 * @data: input data
 *
 * Return: nothing
 */
void exec_cmd(shell_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

/**
 * is_delim - checks if character is a delimeter
 * @l: input character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if not
 */
int is_delim(char l, char *delim)
{
	int i = 0;

	while (delim[i])
	{
		if (delim[i] == l)
			return (1);
	i++;
	}
	return (0);
}

/**
 * is_opperator - test if current char in buffer is a chain delimeter
 * @data: the parameter struct
 * @buffer: the char buffer
 * @index: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_opperator(shell_t *data, char *buffer, size_t *index)
{
	size_t j;

	j = *index;
	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->cmd_opperators = 1;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->cmd_opperators = 2;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		data->cmd_opperators = 3;
	}
	else
		return (0);
	*index = j;
	return (1);
}
