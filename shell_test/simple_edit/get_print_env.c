#include "main.h"

/**
 * _getenv - E
 * @name: ..
 * Return: ..
 */

char *_getenv(const char *name)
{
	char **env = environ;
	size_t name_len = _strlen(name);

	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1);
		}
			env++;
			}

		return (NULL);
}

/**
 * execute_printenv - E
 * @env: ..
 * @var: ..
 */

void execute_printenv(char **env, char *var)
{
	char *value;
	char **envp;

	if (var != NULL)
	{
		value = _getenv(var);
		if (value != NULL)
		{
			printf("%s\n", value);
		}
		else
		{
			fprintf(stderr, "%s: environment variable not found\n", var);
		}
	}
	else
	{
		envp = env;
		while (*envp != NULL)
		{
		printf("%s\n", *envp);
		envp++;
		}
	}
}
