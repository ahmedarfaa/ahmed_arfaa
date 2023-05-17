#include "main.h"

/**
 *
 */

int _sprintf(char *buf, const char *format, ...)
{
    va_list args;
    int len;

    va_start(args, format);
    len = vsprintf(buf, format, args);
    va_end(args);

    return len;
}
