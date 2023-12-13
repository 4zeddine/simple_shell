#include "shell.h"

/**
 * set_history - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int set_history(shell_t *data)
{
	ssize_t fd;
	singl_t *node = NULL;
	char *fn;

	fn = get_hfile(data);
	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		print_string_sfd(node->str, fd);
		print_fd('\n', fd);
	}
	print_fd(-1, fd);
	close(fd);
	return (1);
}

/**
 * get_hfile - gets the history file
 * @data: input data
 *
 * Return: string containg history file
 */

char *get_hfile(shell_t *data)
{
	char *buffer, *d;

	d = _getenv(data, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(d) +
				_strlen(".simple_shell_history") + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, ".simple_shell_history");
	return (buffer);
}

/**
 * build_hlist - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buffer: a buffer
 * @counter: the history line counter
 *
 * Return: 0
 */
int build_hlist(shell_t *data, char *buffer, int counter)
{
	singl_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buffer, counter);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * read_history - reads history from file
 * @data: the parameter struct
 *
 * Return: history counter on success or 0
 */
int read_history(shell_t *data)
{
	int x, last = 0, l_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hfile(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_hlist(data, buf + last, l_count++);
			last = x + 1;
		}
	if (last != x)
		build_hlist(data, buf + last, l_count++);
	free(buf);
	data->his_counter = l_count;
	while (data->his_counter-- >= 4096)
		delete_node_at_index(&(data->history), 0);
	his_recounter(data);
	return (data->his_counter);
}

/**
 * his_recounter - renumbers the history linked list after changes
 * @data: input data
 *
 * Return: the new histcount
 */
int his_recounter(shell_t *data)
{
	singl_t *node;
	int y = 0;

	node = data->history;
	while (node)
	{
		node->num = y;
		node = node->next;
		y++;
	}
	data->his_counter = y;

	return (data->his_counter);
}
