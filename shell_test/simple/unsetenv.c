#include "main.h"

void execute_setenv(char **args) {
    _setenv(&environ, args[1], args[2]);
}

/**
 *
 */

void execute_unsetenv(char **args)
{
    int name_len, i, j;

    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    name_len = _strlen(args[1]);

    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(environ[i], args[1], name_len) == 0 && environ[i][name_len] == '=') {
            free(environ[i]);
            for (j = i; environ[j] != NULL; j++)
	    {
                environ[j] = environ[j + 1];
            }
            return;
        }
    }

    fprintf(stderr, "Variable %s not found\n", args[1]);
}
