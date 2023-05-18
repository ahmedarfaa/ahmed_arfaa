#include "main.h"

/**
 * _snprintf - E
 * @str: ..
 * @size: ..
 * @format: ..
 * Return: ..
 */

int _snprintf(char *str, size_t size, const char *format, ...)
{
	int d, temp;
	char buf[32];
	int n = 0;
	char *s;
	va_list args;
	int len = 0;
	char *p = str;
	const char *fmt = format;

	va_start(args, format);

	while (*fmt != '\0' && len < (int)size - 1)
	{
		if (*fmt == '%')
		{
		fmt++;
		switch (*fmt)
		{
		case 's':
		{
			s = va_arg(args, char *);
		while (*s != '\0' && len < (int)size - 1)
		{
			*p++ = *s++;
			len++;
		}
		break;
		}
		case 'd':
		{
			d = va_arg(args, int);

			temp = d;
		if (d < 0)
		{
			*p++ = '-';
			len++;
		temp = -temp;
		}
		if (temp == 0)
		{
			buf[n++] = '0';
		}
		else
		{
		while (temp > 0)
		{
			buf[n++] = '0' + temp % 10;
			temp /= 10;
		}
		}
		while (n > 0 && len < (int)size - 1)
		{
			*p++ = buf[--n];
			len++;
		}
			break;
		}
		default:
			va_end(args);
			return (-1);
		}
		}
		else
		{
			*p++ = *fmt;
			len++;
		}
			fmt++;
		}

			va_end(args);

		*p = '\0';

		return (len);
}
