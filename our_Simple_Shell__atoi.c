#include "our_simple_shell_shell.h"

/**
 * our_interactive - interactive mode must be returns if the shell is true interactive mode
 * @info: --- The struct address
 *
 *
 * Return: 1 if the shell is a true interactive mode, 0 if not
 */
int ourtion_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * our_is_delim - make sure the character is a delimeter
 *
 * @c: the char to know 
 *
 * @delim: to know the delimeter of string
 *
 * Return: 1 true, if all is YES, 0 false, if all is NO
 */
int ourtion_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * our_isalpha - examine for the alphabetic character
 *
 * @i: The input character 
 *
 * Return: 1 if s is  alphabetic True, 0 if not
 */

int ourtion__isalpha(int i)
{
	if ((i >= 'a' && c <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * our_atoi -  must converts a string number to an \'integer\'
 *
 * @c: the string must be converted
 *
 * @n: the number must be converted
 *
 * Return: 1 when the numbers are still in string, converted number if not
 */

int ourtion__atoi(char *c)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; c[n] != '\0' && flag != 2; n++)
	{
		if (c[n] == '-')
			sign *= -1;

		if (c[n] >= '0' && c[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

