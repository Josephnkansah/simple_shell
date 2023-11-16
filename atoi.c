#include "shell.h"

/**
 * **parse - splits a string into words
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **parse(char *str, char *d)
{
    // Existing implementation of parse function...
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
    // Existing implementation of strtow2 function...
}

/**
 * **mytop - splits a string into words
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **mytop(char *str, char *d)
{
    // Function implementation for mytop
    int i, j, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return (NULL);
    if (!d)
        d = " ";
    for (i = 0; str[i] != '\0'; i++)
        if (!_delimeter(str[i], d) && (_delimeter(str[i + 1], d) || !str[i + 1]))
            numwords++;

    if (numwords == 0)
        return (NULL);
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (_delimeter(str[i], d))
            i++;
        k = 0;
        while (!_delimeter(str[i + k], d) && str[i + k])
            k++;
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = 0;
    }
    s[j] = NULL;
    return (s);
}