#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: void
 */
void _eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_eputchar(str[z]);
		z++;
	}
}

/**
 * _eputchar - writes the character a to stderror
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set automatically.
 */
int _eputchar(char a)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (a != BUF_FLUSH)
		buff[i++] = a;
	return (1);
}

/**
 * _putfd - writes the character a to given fd
 * @a: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set automatically.
 */
int _putfd(char c, int fd)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int y = 0;

	if (!str)
		return (0);
	while (*str)
	{
		y += _putfd(*str++, fd);
	}
	return (y);
}
