#include "main.h" 


int _sprintf(char *buf, const char *format, ...)
{
    int len = 0;
    char *str_arg;
    int int_arg;
    char char_arg;
    int num_digits, temp, i, divisor;

    va_list args;
    va_start(args, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 's':
                    str_arg = va_arg(args, char *);
                    while (*str_arg != '\0')
                    {
                        buf[len++] = *str_arg++;
                    }
                    break;
                case 'd':
                    int_arg = va_arg(args, int);
                    if (int_arg < 0)
                    {
                        buf[len++] = '-';
                        int_arg = -int_arg;
                    }
                    if (int_arg == 0)
                    {
                        buf[len++] = '0';
                    }
                    else
                    {
                        num_digits = 0;
                        temp = int_arg;
                        while (temp > 0)
                        {
                            temp /= 10;
                            num_digits++;
                        }
                        temp = int_arg;
                        divisor = 1;
                        for (i = 1; i < num_digits; i++)
                        {
                            divisor *= 10;
                        }
                        while (num_digits > 0)
                        {
                            int digit = temp / divisor;
                            buf[len++] = '0' + digit;
                            temp -= digit * divisor;
                            divisor /= 10;
                            num_digits--;
                        }
                    }
                    break;
                case 'c':
                    char_arg = va_arg(args, int);
                    buf[len++] = char_arg;
                    break;
                default:
                    buf[len++] = *format;
                    break;
            }
        }
        else
        {
            buf[len++] = *format;
        }
        format++;
    }

    va_end(args);

    buf[len] = '\0';

    return len;
}
