#include "main.h"

/**
 */

size_t _strlen(const char *s)
{

	size_t l = 0;

	while (*s++)
		l++;
	return (l);

}

/**
 *
 */

int _atoi(char *s)
{

int sign = 1;
unsigned int num = 0;

do {

if (*s == '-')
sign *= -1;

else if (*s >= '0' && *s <= '9')
num = (num * 10) + (*s - '0');

else if (num > 0)
break;

} while (*s++);

return (num *sign);
}

/**
 *
 */
char *_memcpy(char *dest, const char *src, unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++) {
        (dest)[i] = (src)[i];
    }
    return dest;
}
/**
 *
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            return s1[i] - s2[i];
        }
        else if (s1[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

/**
 *
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
    return p;
}

/**
 *
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
 *
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
 *
 */
int _isupper(int c)
{

	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);


	return (0);
}
