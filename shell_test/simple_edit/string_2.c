#include "main.h"

/**
 * _strdup - E
 * @s: ..
 * Return: ..
 */

char *_strdup(const char *s)
{
	size_t len;
	char *p;

	len = _strlen(s) + 1;
	p = malloc(len);
	if (p != NULL)
	{
		_memcpy(p, s, len);
	}
		return (p);
}

/**
 * _strcmp - E
 * @s1: ..
 * @s2: ..
 * Return: ..
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);

}
/**
 * _strchr - E
 * @s: ..
 * @c: ..
 * Return: ..
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
		{
			return (s + i);
		}
	}
	return ('\0');

}
/**
 * _isupper - E
 * @c: ..
 * Return: ..
 */
int _isupper(int c)
{

	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);


	return (0);
}

