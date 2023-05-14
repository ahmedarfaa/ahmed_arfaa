#include "main.h"

/**
 *
 */

int _snprintf(char *str, size_t size, const char *format, ...)
{
    va_list args;
    int len = 0;
    char *p = str;
    const char *fmt = format;

    va_start(args, format);

    while (*fmt != '\0' && len < (int)size - 1)
    {
        if (*fmt == '%')
        {
            /* Handle format specifier */
            fmt++;
            switch (*fmt)
            {
                case 's':
                {
                    char *s = va_arg(args, char *);
                    while (*s != '\0' && len < (int)size - 1)
                    {
                        *p++ = *s++;
                        len++;
                    }
                    break;
                }
                case 'd':
                {
                    int d = va_arg(args, int);
                    char buf[32];
                    int n = snprintf(buf, sizeof(buf), "%d", d);
                    if (n < 0 || len + n >= (int)size)
                    {
                        /* Error or buffer overflow */
                        va_end(args);
                        return -1;
                    }
                    memcpy(p, buf, n);
                    p += n;
                    len += n;
                    break;
                }
                /* Handle other format specifiers as needed */
                default:
                    /* Unsupported format specifier */
                    va_end(args);
                    return -1;
            }
        }
        else
        {
            /* Handle regular character */
            *p++ = *fmt;
            len++;
        }
        fmt++;
    }

    va_end(args);

    /* Null-terminate the string */
    *p = '\0';

    return len;
}
