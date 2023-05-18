#include "main.h"

/**
 * execute_echo - E
 * @args: array of arguments
 * @status: exit status
 * Return: void
 */
void execute_echo(char **args, int status)
{
    int i;

    for (i = 1; args[i] != NULL; i++)
    {
        if (_strcmp(args[i], "$$") == 0)
        {
            pid_t value = getpid();
            if (value >= 0)
            {
                char pid_str[10];
                _sprintf(pid_str, "%d", value);
                write(STDOUT_FILENO, pid_str, _strlen(pid_str));
                
            }
        }
        else if (_strncmp(args[i], "$?", 2) == 0)
        {
            char exit_status[10];
            _sprintf(exit_status, "%d", WEXITSTATUS(status));
            write(STDOUT_FILENO, exit_status, _strlen(exit_status));
            
        }
        else
        {
            write(STDOUT_FILENO, args[i], _strlen(args[i]));
            write(STDOUT_FILENO, " ", 1);
        }
    }

    write(STDOUT_FILENO, "\n", 1);
}