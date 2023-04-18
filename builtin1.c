#include "shell.h"

/**
 * _myhistory - displays the history list one command by line and precedes
 *              with line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - sets aliases to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *information, char *str)
{
	char *b, c;
	int ret;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	c = *b;
	*b = 0;
	ret = delete_node_at_index(&(information->alias),
		get_node_index(information->alias, node_starts_with(information->alias, str, -1)));
	*b = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *information, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(information, str));

	unset_alias(information, str);
	return (add_node_end(&(information->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *information)
{
	int a = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (information->argc == 1)
	{
		node = information->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; information->argv[a]; a++)
	{
		b = _strchr(information->argv[a], '=');
		if (b)
			set_alias(information, information->argv[a]);
		else
			print_alias(node_starts_with(information->alias, information->argv[a], '='));
	}

	return (0);
}
