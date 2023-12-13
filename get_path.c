#include "shell.h"

/**
 * is_cmd - check if input is a command
 * @data: input data
 * @path: path to the file
 *
 * Return: 1 if true, 0 if not
 */
int is_cmd(shell_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * find_path - finds this cmd in the PATH string
 * @data: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(shell_t *data, char *path_str, char *cmd)
{
	char *path;
	int i = 0, pos = 0;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && check_start(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!path_str[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * dup_chars - duplicates characters
 * @str_path: path string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *str_path, int start, int end)
{
	static char buffer[BUFF_SIZE];
	int i = 0, a = 0;

	for (a = 0, i = start; i < end; i++)
		if (str_path[i] != ':')
			buffer[a++] = str_path[i];
	buffer[a] = 0;
	return (buffer);
}
