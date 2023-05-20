#include "main.h"

/**
 * execute_commands_from_file - E
 * @filename: ..
 * @env: ..
 */

void execute_commands_from_file(char *filename, char **env)
{
	char *input = NULL, *args[SIZE], *token, *fullpath;
	char *commands[SIZE / 2 + 1];
	size_t input_size = 0;
	ssize_t read;
	int status, i, c, num_commands, count = 0;
	pid_t pid;
	char error_message[50];
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp == NULL)
		perror("Error opening file"), exit(1);
	while ((read = getline(&input, &input_size, fp)) != -1)
	{
	if (input[read - 1] == '\n')
		input[read - 1] = '\0';
	num_commands = 0;
	commands[num_commands] = _stringtok(input, ";");
	while (commands[num_commands] != NULL)
		num_commands++, commands[num_commands] = _stringtok(NULL, ";");
	for (c = 0; c < num_commands; c++)
	{
		token = _stringtok(commands[c], " "), i = 0;
	while (token != NULL)
	{
		args[i] = token, i++, token = _stringtok(NULL, " ");
	}
		args[i] = NULL;
	if (execute_command(args, env, &status) == -1)
	{	fullpath = find_executable(args[0], env), pid = fork();
	if (pid == 0)
	{
		if (execve(fullpath, args, env) == -1)
		{
		_sprintf(error_message, "./hsh: %d: %s: not found\n", count, args[0]);
		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(127);
		}
	}
	else if (pid < 0)
		perror("fork"), exit(1);
	else
		waitpid(pid, &status, 0);
	}
	}
	}
	fclose(fp);
	free(input);
}
