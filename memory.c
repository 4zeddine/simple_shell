#include "shell.h"

/**
 * free_p - frees a pointer and NULLs it
 * @ptr: pointer to be free
 *
 * Return: 1 if freed or 0 if not.
 */
int free_p(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_array - frees an array of strings
 * @array: input array of strings
 */
void free_array(char **array)
{
	char **a = array;

	if (!array)
		return;
	while (*array)
		free(*array++);
	free(a);
}

/**
 * init_data - initializes the struct
 * @data: input struct
 * @argv: argument vector
 */
void init_data(shell_t *data, char **argv)
{
	int i = 0;

	data->fname = argv[0];
	if (data->args)
	{
		data->argv = __strtok(data->args, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->args);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replace_alias(data);
		replace_vars(data);
	}
}

/**
 * free_data - frees the struct fields
 * @data: input data
 * @bool: condition for freeing all fields
 */
void free_data(shell_t *data, int bool)
{
	free_array(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (bool)
	{
		if (!data->cmd_buff)
			free(data->args);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		free_array(data->environ);
			data->environ = NULL;
		free_p((void **)data->cmd_buff);
		if (data->readfd > 2)
			close(data->readfd);
		print_char(-1);
	}
}


