#include "main.h"

/**
 *
 */
void execute_clear(void)
{
    system("clear");
}

/**
 *
 */

void execute_cd(char **args)
{
	char *home = _getenv("HOME");
    if (args[1] == NULL)
    {
        chdir(home);
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
}

/**
 *
 *
 */
void execute_exit(char **args)
{
    if (args[1] != NULL)
    {
        int exit_code = atoi(args[1]);
        exit(exit_code);
    }
    else
    {
       exit (0);
    }
}
