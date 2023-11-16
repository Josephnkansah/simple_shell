#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **argv)
{
	ssize_t input_result = 0;
	int builtin_return = 0;

	while (input_result != -1 && builtin_return != -2)
	{
		remove_info(info);
		if (active(info))
			_puts("CustomShell===>$ ");
		_eputchar(BUF_FLUSH);
		input_result = get_input(info);
		if (input_result != -1)
		{
			s_info(info, argv);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_command(info);
		}
		else if (active(info))
			_putchar('\n');
		let_info(info, 0);
	}
	write_history(info);
	let_info(info, 1);
	if (!active(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _env},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_string_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_return = builtintbl[i].func(info);
			break;
		}
	return (built_in_return);
}

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, argument_count;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, argument_count = 0; info->arg[i]; i++)
		if (!_delimeter(info->arg[i], " \t\n"))
			argument_count++;
	if (!argument_count)
		return;

	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((active(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			let_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
