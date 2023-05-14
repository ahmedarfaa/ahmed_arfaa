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
	memcpy(dest, src, n);
	return (dest);
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
