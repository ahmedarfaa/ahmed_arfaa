#include "main.h"

/**
 * main - E
 * @argc: ..
 * @argv: ..
 * @env: ..
 * Return: 0 insuccess.
 */

int main(int argc, char **argv, char **env)
{
	char *input = NULL, *args[SIZE], *token, *filename, *fullpath;
	char *commands[SIZE / 2 + 1];
	size_t input_size = 0;
	ssize_t read;
	int status, i, c, num_commands, count = 0;
	struct stat st;
	pid_t pid;
	char error_message[50];
	bool from_pipe = false;
	(void) argv;

	if (argc > 1)
	{
	execute_commands_from_file(argv[1], env);
	return (0);
	}
	if (fstat(STDIN_FILENO, &st) == 0 && S_ISFIFO(st.st_mode))
	from_pipe = true;
	while (1 && !from_pipe)
	{
		count++;
		write(STDOUT_FILENO, "$ ", 2);
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
			args[i] = token, i++, token = _stringtok(NULL, " ");
		args[i] = NULL;
		if (execute_command(args, env, &status) == -1)
		{
		filename = args[0];
		fullpath = find_executable(filename, env), pid = fork();
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

	free(input);
	return (0);
}
