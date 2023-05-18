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
	char *input = NULL, *args[SIZE], *token, *filename, *full_path;
	char *commands[SIZE / 2 + 1];
	size_t input_size = 0;
	ssize_t read;
	int status, i, c, num_commands;
	pid_t pid;
	bool from_pipe = false;
	struct stat st;
	(void) argv;

	if (fstat(STDIN_FILENO, &st) == 0 && S_ISFIFO(st.st_mode))
	{
	from_pipe = true;
	}

	while (1 && !from_pipe)
	{

		write(STDOUT_FILENO, "$ ", 2);
		read = getline(&input, &input_size, stdin);
	if (read == -1)
	{
		exit(1);
	}
	if (input[read - 1] == '\n')
	{
		input[read - 1] = '\0';
	}
	if (input[0] == '\0')
	{
		continue;
	}
	num_commands = 0;
	commands[num_commands] = __strtok(input, ";");
	while (commands[num_commands] != NULL)
	{
		num_commands++;
		commands[num_commands] = __strtok(NULL, ";");
	}
	for (c = 0; c < num_commands; c++)
	{
		token = __strtok(commands[c], " ");
		i = 0;
		while (token != NULL)
				args[i] = token, i++, token = __strtok(NULL, " ");

			args[i] = NULL;
		if (execute_command(args, env, &status) == -1)
		{
			filename = args[0];
			full_path = find_executable(filename, env);
			pid = fork();
		if (pid == 0)
		{
			execute_command_with_redirection(args, full_path);
			perror("execve");
			exit(1);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	}
	}
	free(input);
	return (0);
}
