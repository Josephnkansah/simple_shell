#include "our_simple_shell_shell.h"

/**
 * ourtion__eputs - To prints an input string _ourtion
 *
 * @str: The string must be printed
 *
 *
 * Return: 0
 */
void ourtion__eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		ourtion__eputchar(str[n]);
		n++;
	}
}

/**
 * ourtion__eputchar - All is to writes the character of c to stderr
 * @c: The character to be print
 *
 * Return: On victory  1, On mistake, -1 is returned
 * and errno is set appropriately.
 */
int ourtion__eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * ourtion__putfd - This means to writes the character of c to given fd /putfd
 *
 * @c: The character is to be print
 *
 * @fd: The filedescriptor to write to
 *
 * Return: On victory 1.
 * On mistake, -1 is returned
 * and errno is set appropriately.
 */
int ourtion__putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * ourtion__putsfd - To prints an input of string
 * @str: The string is to be printed
 * @fd: The filedescriptor is to be write 
 *
 * Return: always the number of chars put
 */
int ourtion__putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += myfun__putfd(*str++, fd);
	}
	return (n);
}
