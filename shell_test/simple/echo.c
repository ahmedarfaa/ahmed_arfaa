#include "main.h"

/**
 * execute_echo - E
 * @args: ..
 * status: ..
 * @env: ..
 * Return: void
 *
 */

void execute_echo(char **args, int status, char **env)
{
	int i, fd;
	bool redirect_output = false;

	int stdout_fd = _dup(STDOUT_FILENO);

	for (i = 1; args[i] != NULL; i++)
	{
		if (_strcmp(args[i], ">") == 0)
		{
			redirect_output = true;
			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
			if (_dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
			close(fd);
			args[i] = NULL;
			break;
		}
	}

		for (i = 1; args[i] != NULL; i++)
		{
			if (i > 1)
			{
			write(STDOUT_FILENO, " ", 1);
			}
			else if (args[i][0] == '"' || args[i][0] == '\'')
			{
				char *end_quote = _strchr(args[i] + 1, args[i][0]);
			if (end_quote != NULL)
			{
				write(STDOUT_FILENO, args[i] + 1, end_quote - args[i] - 1);
			write(STDOUT_FILENO, "\n", 1);
			}
			else
			{
			write(STDOUT_FILENO, args[i] + 1, _strlen(args[i]) - 1);
			write(STDOUT_FILENO, "\n", 1);
			}
			}
			else if (_strncmp(args[i], "$?", 2) == 0)
			{
				char exit_status[10];
				_sprintf(exit_status, "%d", WEXITSTATUS(status));
				write(STDOUT_FILENO, exit_status, _strlen(exit_status));
				write(STDOUT_FILENO, "\n", 1);
			}
			else if (args[i][0] == '$')
			{
			if (args[i][1] == '\0')
			{
				write(STDOUT_FILENO, args[i], _strlen(args[i]));
				write(STDOUT_FILENO, "\n", 1);
			}
			else if (args[i][1] == '$')
			{
				pid_t value = getpid();
			if (value >= 0)
			{
				printf("%d\n", value);
			}
			}
			else
			{
				execute_printenv(env, args[i] + 1); /** Print the value of the variable */
			}
			}
			else if (_isupper(args[i][0]))
			{

				execute_printenv(env, args[i]); /** Print the value of the variable */
			}
			else
			{
				write(STDOUT_FILENO, args[i], _strlen(args[i]));
				write(STDOUT_FILENO, "\n", 1);
			}
			}

			if (redirect_output)
			{
			if (dup2(stdout_fd, STDOUT_FILENO) == -1)
			{
			perror("dup2");
			exit(1);
			}
			close(stdout_fd);
			}
}
