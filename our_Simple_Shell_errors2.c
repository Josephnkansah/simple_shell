#include "our_simple_shell_shell.h"
/**
 * ourtion__erratoi - This means converts a string to an integer _ourtion
 *
 * @s: The string is to be converted
 *
 * Return: always 0 if there is no numbers in string,
 *  or converted number -1 on error
 */
int ourtion__erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why is it that this make main return 255? */
	for (n = 0;  s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * ourtion_print_error - must to be prints an error messages of all
 *
 * @info: The parameter and the return info struct
 *
 * @estr: The string containing that is be specified error type
 *
 * Return: 0 if there is no numbers in string,
 * or converted number -1 on error
 */
void ourtion_print_error(info_t *info, char *estr)
{
	ourtion__eputs(info->fname);
	ourtion__eputs(": ");
	ourtion_print_d(info->line_count, STDERR_FILENO);
	ourtion__eputs(": ");
	ourtion__eputs(info->argv[0]);
	ourtion__eputs(": ");
	ourtion__eputs(estr);
}

/**
 * ourtion_print_d - The function that must prints a decimal number
 *
 * @input: The input
 *
 * @fd: The filedescriptor is to be write
 *
 * Return: Always return thr number of characters printed
 */
int ourtion_print_d(int input, int fd)
{
	int (*__putchar)(char) = ourtion__putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = ourtion__eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * ourtion_convert_number - To converter the function, and a clone of itoa
 *
 * @base: The base
 *
 * @flags: The argument flags
 * @num: The number
 * Return: Always string
 */
char *ourtion_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * ourtion_remove_comments - The function replaces first instance of the '#' with '\0'
 * @buf: The address of the string that must be  modify
 *
 * Return: 0;
 */
void ourtion_remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}

