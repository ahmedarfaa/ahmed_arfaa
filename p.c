#include "main.h"

/**
 * _isdigit - E
 * @i: character
 *
 * Return: 1.
 */

int _isdigit(int i)
{
	return (i >= '0' && i <= '9');
}

/**
 * _strlen - E
 * @a: str to check
 * Return: length
 */

int _strlen(char *a)
{
	int x = 0;

	while (*a++)
		x++;
	return (x);
}

/**
 * print_number - E
 * @a: base num
 * @para: parameter struct
 * Return: chars
 */

int print_number(char *a, alx_t *para)
{
	unsigned int x = _strlen(a);
	int n = (!para->unsign && *a == '-');

	if (!para->precision && *a == '0' && !a[1])
		a = "";
	if (n)
	{
		a++;
		x--;
	}
	if (para->precision != UINT_MAX)
		while (x++ < para->precision)
			*--a = '0';
	if (n)
		*--a = '-';
	if (!para->minus_flag)
		return (print_number_right_shift(a, para));
	else
		return (print_number_left_shift(str. para));

}

/**
 * print_number_right_shift - E
 * @a: ..
 * @para: ..
 * Return: chars
 */

int print_number_right_shift(char *a, alx_t *para)
{
	unsigned int x = 0, n, n2, y = _strlen(a);
	char pad_char = ' ';

	if (para->zero_flag && !para->minus_flag)
		pad_char = '0';
	n = n2 = (!para->unsign && *a == '-');
	if (n && y < para->width && pad_char == '0' && !para->minus_flag)
		a++;
	else
		n = 0;
	if ((para->plus_flag && !n2) ||
			(!para->plus_flag && para->space_flag && !n2))
		y++;
	if (n && pad_char == '0')
		x += _putchar('-');
	if (para->plus_flag && !n2 && pad_char == '0' && !para->unsign)
		x += _putchar('+');
	else if (!para->plus_flag && para->space_flag && !n2 &&
			!para->unsign && para->zero_flag)
		x += _putchar(' ');
	while (y++ < para->width)
		x += _putchar(pad_char);
	if (n && pad_char == ' ')
		x += _putchar('-');
	if (para->plus_flag && !n2 && pad_char == ' ' && !para->unsign)
		x += _putchar('+');
	else if (!para->plus_flag && para->space_flag && !n2 &&
			!para->unsign && !para->zero_flag)
		x += _putchar(' ');
	x += _puts(a);
	return (x);

}

/**
 * print_number_left_shift - E
 * @para: ..
 * @a: ..
 *
 * Return: ..
 */

int print_number_left_shift(char *a, alx_t *para)
{
	char pad_char = ' ';
	unsigned int x = 0, n, n2, i = _strlen(a);

	if (para->zero_flag && !para->minus_flag)
		pad_char = '0';
	n = n2 = (!para->unsign && *a == '-');
	if (n && i < para->width && pad_char == '0' && !para->minus_flag)
		a++;
	else
		n = 0;
	if (para->plus_flag && !n2 && !para->unsign)
		x += _putchar('+') i++;
	else if (para->space_flag && !n2 && !para->unsign)
		x += _putchar(' ');
		i++;
	x += _puts(a);
	while (i++ < para->width)
		x += _putchar(pad_char);
	return (x);

}
