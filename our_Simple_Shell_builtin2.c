#include "our_Simple_Shell_shell.h"

/**
 * ourtion_unset_alias - The sets of alias to be string _ourtion
 * @info: The  parameter of the struct
 * @str: is  string alias
 *
 * Return: Always 0 on victory, 1 on fail
 */
int ourtion_unset_alias(info_t *info, char *str)
{
	char *p, o;
	int ret;

	p = ourtion__strchr(str, '=');
	if (!p)
		return (1);
	o = *p;
	*p = 0;
	ret = ourtion_delete_node_at_index(&(info->alias),
		ourtion_get_node_index(info->alias, ourtion_node_starts_with(info->alias, str, -1)));
	*p = o;
	return (ret);
}

/**
 * ourtion_print_alias - list\ prints an alias of the string
 * @node: the alias of the node
 *
 * Return: Always 0 on victory, 1 on fail
 */
int ourtion_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = ourtion__strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		ourtion__putchar(*a);
		ourtion__putchar('\'');
		ourtion__puts(p + 1);
		ourtion__puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ourtion__ourhistory - let exhibit all the history list, however one command by each line, succeed
 * with line numbers, beginning at 0.
 * @info: construction carrying potential arguments. That is been used to maintain
 * function prototype.
 *  Return: Always 0
 */
int ourtion__ourhistory(info_t *info)
{
	ourtion_print_list(info->history);
	return (0);
}

/**
 * ourtion_set_alias - makes\ sets alias to string
 * @info: The parameter of the struct
 * @str: string of the alias
 *
 * Return: Always 0 on victory, 1 on fail
 */
int ourtion_set_alias(info_t *info, char *str)
{
	char *p;

	p = ourtion__strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (ourtion_unset_alias(info, str));

	ourtion_unset_alias(info, str);
	return (ourtion_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * ourtion__ouralias - The mimics of the alias builtin
 * @info: construction carrying potential arguments. must used to maintain
 * function prototype.
 * Return: 0 Always
 */
int ourtion__ouralias(info_t *info)
{
	int u = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			ourtion_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (u = 1; info->argv[u]; u++)
	{
		p = ourtion__strchr(info->argv[u], '=');
		if (p)
			ourtion_set_alias(info, info->argv[u]);
		else
			ourtion_print_alias(ourtion_node_starts_with(info->alias, info->argv[u], '='));
	}

	return (0);
}
int ourtion__getline(info_t *, char **, size_t *)
{
    return 0;
}

