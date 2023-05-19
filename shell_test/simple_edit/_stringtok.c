#include "main.h"

/**
 * _equal2 - E
 * @cut: ..
 * @str: ..
 * Return: ..
 */

unsigned int _equal2(char cut, const char *str)
{
	unsigned int index = 0;

	while (str[index] != 0)
	{
		if (cut == str[index])
		{		return (0);
		}
		index++;
	}
	return (1);
}

/**
 * _stringtok - E
 * @string: ..
 * @cutter: ..
 * Return: ..
 */

char *_stringtok(char *string, const char *cutter)
{
	static char *ftok;
	static char *stok;
	long int i;

	if (string == NULL && cutter == NULL)
		return (NULL);
	if (string != NULL)
	{
		stok = string;
	}
	ftok = stok;
	if (ftok == NULL)
		return (NULL);
	for (i = 0; stok[i] != 0; i++)
	{
		if (_equal2(stok[i], cutter) == 1)
			break;
	}
	if (stok[i] == 0 || stok[i] == 35)
	{
		return (NULL);
	}
		ftok = stok + i;
		stok = ftok;
	for (i = 0; stok[i] != 0; i++)
	{
		if (_equal2(stok[i], cutter) == 0)
			break;
	}
	if (stok[i] == 0)
		stok = NULL;
	else
	{
		stok[i] = 0;
		stok += i + 1;
	}
	return (ftok);
}
