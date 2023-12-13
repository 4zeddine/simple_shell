#include "shell.h"

/**
 * print_list - prints a list
 * @list: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const singl_t *list)
{
	size_t i = 0;

	while (list)
	{
		print_string(convert_number(list->num, 10, 0));
		print_char(':');
		print_char(' ');
		print_string(list->str ? list->str : "(nil)");
		print_string("\n");
		list = list->next;
		i++;
	}
	return (i);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(singl_t *head, singl_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * check_node_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
singl_t *check_node_start(singl_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = check_start(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * list_to_strings - returns an array of strings of the list
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(singl_t *head)
{
	singl_t *node = head;
	size_t i, j;
	char **array;
	char *str;

	i = list_size(head);
	if (!head || !i)
		return (NULL);

	array = malloc(sizeof(char *) * (i + 1));

	if (!array)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(array[j]);
			free(array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		array[i] = str;
	}
	array[i] = NULL;
	return (array);
}

/**
 * list_size - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_size(const singl_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
