#include "shell.h"

/**
 * print_list_str - prints strings of a list
 * @list: pointer to first node
 *
 * Return: size of the list
 */
size_t print_list_str(const singl_t *list)
{
	size_t i = 0;

	while (list)
	{
		if (list->str)
			print_string(list->str);
		else
			print_string("(nil)");
		print_string("\n");
		list = list->next;
		i++;
	}
	return (i);
}

/**
 * add_node_start - adds a node at the start of the list
 * @head: pointer to head node
 * @str: string of node
 * @num: node index
 *
 * Return: size of list
 */
singl_t *add_node_start(singl_t **head, const char *str, int num)
{
	singl_t *new;

	if (!head)
		return (NULL);

	new = malloc(sizeof(singl_t));

	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(singl_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - adds a node at the end of the list
 * @head: pointer to head node
 * @str: string of node
 * @num: node index
 *
 * Return: size of list
 */
singl_t *add_node_end(singl_t **head, const char *str, int num)
{
	singl_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(singl_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(singl_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * delete_node_at_index - deletes node at an index
 * @head: pointer to first node
 * @index: index to delete
 *
 * Return: 1 if successful or 0 if not
 */
int delete_node_at_index(singl_t **head, unsigned int index)
{
	singl_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees nodes of a list
 * @head_ptr: pointer to head node
 *
 * Return: nothing
 */
void free_list(singl_t **head_ptr)
{
	singl_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
