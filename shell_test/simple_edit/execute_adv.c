#include "main.h"

/**
 * execute_command - execute a command
 * @args: array of arguments
 * @env: environment variables
 * @status: exit status
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char **env, int *status)
{
	if (_strcmp(args[0], "cd") == 0)
	{
		execute_cd(args);
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		execute_exit(args);
	}
	else if (_strcmp(args[0], "printenv") == 0 || _strcmp(args[0], "env") == 0)
	{
	if (args[1] != NULL)
	{
		execute_printenv(env, args[1]);
	}
	else
	{
		execute_printenv(env, NULL);
	}
	}
	else if (_strncmp(args[0], "$", 1) == 0)
	{
		execute_printenv(env, args[0] + 1);
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		execute_setenv(args);
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		execute_unsetenv(args);
	}
	else if (_strcmp(args[0], "echo") == 0)
	{
		if (_strcmp(args[1], "$$") == 0)
		{
			execute_echo(args, *status);
			return (0);
		}
		else if (_strcmp(args[1], "$?") == 0)
		{
			execute_echo(args, *status);
			return (0);
		}
		else if ((_strcmp(args[1], "$") == 0) && (_isupper(args[1][1])))
		{
			execute_echo(args, *status);
			return (0);
		}
		else
			return (-1);
	}

	else if (_strcmp(args[0], "clear") == 0)
	{
		execute_clear();
	}
	else
	{
		return (-1);
	}
	return (0);
}
