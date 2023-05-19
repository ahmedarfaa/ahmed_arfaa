#include "main.h"
/**
 * main - main Entry
 * @argc: V
 * @argv: V
 * @env: P
 * Return: 0 in success.
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	char *input = NULL, *args[SIZE], *token, *filename, *fullpath;
	char *commands[SIZE / 2 + 1];
	size_t input_size = 0;
	ssize_t read;
	int status, i, c, num_commands;
	struct stat st;
	pid_t pid, original = getppid(), new = getppid();
	bool from_pipe = false;
	(void) argv;

	if (fstat(STDIN_FILENO, &st) == 0 && S_ISFIFO(st.st_mode))
	from_pipe = true;
	while (1 && !from_pipe)
	{
		if (new == original)
		write(STDOUT_FILENO, "$ ", 2);
		else
		write(STDOUT_FILENO, " ($) ", 5);
		read = getline(&input, &input_size, stdin);
	if (read == -1)
		exit(1);
	if (input[read - 1] == '\n')
		input[read - 1] = '\0';
	if (input[0] == '\0')
		continue;
	num_commands = 0;
	commands[num_commands] = _stringtok(input, ";");
	while (commands[num_commands] != NULL)
		num_commands++, commands[num_commands] = _stringtok(NULL, ";");
	for (c = 0; c < num_commands; c++)
	{
		token = _stringtok(commands[c], " "), i = 0;
		while (token != NULL)
		{		args[i] = token, i++, token = _stringtok(NULL, " ");
		}		args[i] = NULL;
		if (execute_command(args, env, &status) == -1)
		{
			filename = args[0];
			fullpath = find_executable(filename, env), pid = fork();
			if (pid == 0)
			{	execute_command_with_redirection(args, fullpath, env);
				perror("execve"), exit(1);	}
			else if (pid < 0)
				perror("fork"), exit(1);
			else
				new = getppid(), waitpid(pid, &status, 0);
	}	}	}
	free(input);
	return (0);	}
