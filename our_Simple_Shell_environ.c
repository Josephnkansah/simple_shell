#include "our_simple_shell_shell.h"

/**
 * ourtion_populate_env_list - This means to populates env linked list ourtion_
 * @info: The Structure containing potential arguments.
 *
 *
 * function prototype
 *
 * Return: 0 
 */
int ourtion_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		ourtion_add_node_end(&node, environ[n], 0);
	info->env = node;
	return (0);
}

/**
 * ourtion__ourunsetenv - This means to Remove an environment of a variable
 *
 * @info: The Structure containing potential arguments.
 *
 * constant function prototype
 *
 * Return: 0
 */
int ourtion__orunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		ourtion__eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		ourtion__unsetenv(info, info->argv[n]);

	return (0);
}

/**
 * ourtion__getenv - That means to gets  the value of an environ variable
 *
 * @info: The Structure containing potential arguments.
 *
 * @name: env var name
 *
 * Return: value
 */
char *ourtion__getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = ourtion_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * ourtion__oursetenv - That means to Initialize a new environment variable,
 * / modify an existing one
 * @info: Structure containing potential arguments.
 *
 * function prototype.
 *  Return: 0 Always 
 */
int ourtion__oursetenv(info_t *info)
{
	if (info->argc != 3)
	{
		ourtion__eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (ourtion__setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}



/**
 * ourtion__ourenv - To prints all the  current environment
 *
 * @info: The Structure containing potential arguments.
 *
 * function prototype.
 *
 * Return: Always 0
 */
int ourtion__ourtionenv(info_t *info)
{
	ourtion_print_list_str(info->env);
	return (0);
}

