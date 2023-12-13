#include "shell.h"

/**
 * handl_signal - blocks the CTRL-C
 * @signal: signal number
 *
 * Return: nothing
 */
void handl_signal(int signal)
{
	(void)signal;
	print_string("\n");
	print_string("$ ");
	print_char(-1);
}


/**
 * command_buffer - buffers the commands
 * @data: input data
 * @buffer: pointer to buffer
 * @len: pointer to len var
 *
 * Return: the bytes read
 */
ssize_t command_buffer(shell_t *data, char **buffer, size_t *len)
{
	ssize_t num = 0;
	size_t pt = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handl_signal);
		#if CALL_GETLINE
				num = getline(buf, &pt, stdin);
		#else
				num = _getline(data, buffer, &pt);
		#endif
		if (num > 0)
		{
			if ((*buffer)[num - 1] == '\n')
			{
				(*buffer)[num - 1] = '\0';
				num--;
			}
			data->linecount_flag = 1;
			remove_comments(*buffer);
			build_hlist(data, *buffer, data->his_counter++);
				*len = num;
				data->cmd_buff = buffer;
		}
	}
	return (num);
}


/**
 * get_command - gets a line minus the newline
 * @data: input data
 *
 * Return: bytes read
 */
ssize_t get_command(shell_t *data)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t n = 0;
	char **tokens, *p;


	print_char(-1);
	n = command_buffer(data, &buffer, &len);
	if (n == -1)
	return (-1);
	tokens = &(data->args);
	if (len)
	{
		j = i;
		p = buffer + i;

		check_chain(data, buffer, &j, i, len);
		while (j < len)
		{
			if (is_opperator(data, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_opperators = 0;
		}

		*tokens = p;
		return (_strlen(p));
	}
	*tokens = buffer;
	return (n);
}
