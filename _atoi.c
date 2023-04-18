#include "shell.h"

/**
 * interactive shell - returns true if shell is interactive mode
 * @information: structs addresses
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfwd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char y, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == y)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int y)
{
	if ((y >= 'a' && y <= 'z') || (y >= 'A' && y <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an int
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *c)
{
	int a, sign = 1, flag = 0, output;
	unsigned int results = 0;

	for (a = 0;  c[a] != '\0' && flag != 2; a++)
	{
		if (c[a] == '-')
			sign *= -1;

		if (c[a] >= '0' && c[a] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (c[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -results;
	else
		output = results;

	return (output);
}
