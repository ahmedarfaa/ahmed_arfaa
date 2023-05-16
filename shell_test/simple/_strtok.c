#include "main.h"

/**
 */

unsigned int _equal(char cut, const char *string)
{
	unsigned int index = 0;

	while (string[index] != 0)
	{
		if (cut == string[index])
			return (0);
		index++;
	}
	return (1);
}

/**
 */

char *__strtok(char *string, const char *cutter)
{
	static char *firstTok;
	static char *secondTok;
	long int i;

	if (string == NULL && cutter == NULL)
		return (NULL);
	if (string != NULL)
		secondTok = string;
	firstTok = secondTok;
	if (firstTok == NULL)
		return (NULL);
	for (i = 0; secondTok[i] != 0; i++)
	{
		if (_equal(secondTok[i], cutter) == 1)
			break;
	}
	if (secondTok[i] == 0 || secondTok[i] == 35)
	{
		return (NULL);
	}
	firstTok = secondTok + i;
	secondTok = firstTok;
	for (i = 0; secondTok[i] != 0; i++)
	{
		if (_equal(secondTok[i], cutter) == 0)
			break;
	}
	if (secondTok[i] == 0)
		secondTok = NULL;
	else
	{
		secondTok[i] = 0;
		secondTok += i + 1;
	}
	return (firstTok);
}
