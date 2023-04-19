#include "shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *information, character **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(information);
		if (r != -1)
		{
			set_info(information, argv);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information>status)
		exit(information>status);
	if (builtin_ret == -2)
	{
		if (information>err_num == -1)
			exit(information>status);
		exit(information>err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return information struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *information)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (_strcmp(information>argv[0], builtintbl[y].type) == 0)
		{
			information>line_count++;
			built_in_ret = builtintbl[y].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in the PATH
 * @info: the parameter & return information struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int j, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
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
