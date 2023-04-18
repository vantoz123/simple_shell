#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments and used to maintain
 *          constant function prototype.
 *  Return: exits with the given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *information)
{
	int exitcheck;

	if (information->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(information->argv[1]);
		if (exitcheck == -1)
		{
			information->status = 2;
			print_error(information, "Illicit number: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *information)
{
	char *a, *dir, buffer[1024];
	int cd_ret;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure errormsg here<<\n");
	if (!information->argv[1])
	{
		dir = _getenv(information, "HOME=");
		if (!dir)
			cd_ret = /* TODO: what should this be?? */
				chdir((dir = _getenv(information, "PWD=")) ? dir : "/");
		else
			cd_ret = chdir(dir);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		cd_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(information, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_ret = chdir(information->argv[1]);
	if (cd_ret == -1)
	{
		print_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *information)
{
	char **argument_array;

	argument_array = information->argv;
	_puts("helps call work, Function not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp att_unused work_around */
	return (0);
}
