#include "our_simple_shell_shell.h"

/**
 * ourtion_ourexit - must exits the current shell
 * @info: The potential arguments Structure.
 *
 * Return: exits with a better exit status
 * (0) if info.argv[0] != "exit"
 */
int ourtion_ourexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = ourtion__erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			ourtion_print_error(info, "Illegal number: ");
			ourtion__eputs(info->argv[1]);
			ourtion__eputchar('\n');
			return (1);
		}
		info->err_num = ourtion__erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * ourtion__ourcd - must really changed the current directory of the ongoing process
 * @info: The potential arguments Structure. Made to maintain
 *
 *
 * Return 0 Always to
 */
int ourtion__ourcd(info_t *info)
{
	char *c, *dir, buffer[1024];
	int chdir_ret;

	c = getcwd(buffer, 1024);
	if (!c)
		ourtion__puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = ourtion__getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what will be this? */
				chdir((dir = ourtion__getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (ourtion__strcmp(info->argv[1], "-") == 0)
	{
		if (!ourtion__getenv(info, "OLDPWD="))
		{
			ourtion__puts(c);
			ourtion__putchar('\n');
			return (1);
		}
		ourtion__puts(ourtion__getenv(info, "OLDPWD=")), ourtion__putchar('\n');
		chdir_ret = /* TODO: what will be this? */
			chdir((dir = ourtion__getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		ourtion_print_error(info, "can't cd to ");
		ourtion__eputs(info->argv[1]), ourtion__eputchar('\n');
	}
	else
	{
		ourtion__setenv(info, "OLDPWD", ourtion__getenv(info, "PWD="));
		ourtion__setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ourtion_ourhelp - must to be changed the new directory of the process
 * @info: The potential arguments Structure made to maintain
 *
 * function prototype
 * Return:  0 Always
 */
int ourtion__ourhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	ourtion__puts("always help call works. Function not yet implemented \n");
	if (0)
		ourtion__puts(*arg_array); /* temp for the att_unused put-together */
	return (0);
}

