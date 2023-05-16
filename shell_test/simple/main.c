#include "main.h"

/**
 *
 */
int main(int __attribute__((unused)) argc, char ** __attribute__((unused)) argv, char **env)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read;
    char *args[SIZE];
    int status;
    char *token;
    int i, c;
    pid_t pid;
    char *filename;
    char *full_path;
    bool from_pipe = false;
    pid_t original, chang;
    int num_commands;
    char *commands[SIZE / 2 + 1];
    struct stat st;
    (void) argv;

    original = getppid();
    chang = getppid();

    if (fstat(STDIN_FILENO, &st) == 0 && S_ISFIFO(st.st_mode)) {
    from_pipe = true;
    }
    while (1 && !from_pipe)
    {

       if (chang != original)
        {
            write(STDOUT_FILENO, " ($) ", 5);

        }
        else if (chang == original)
        {
            write(STDOUT_FILENO, "$ ", 2);
        }
        if ((read = getline(&input, &input_size, stdin)) == -1)
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

        /** Split input into commands */
        num_commands = 0;
        commands[num_commands] = __strtok(input, ";");
        while (commands[num_commands] != NULL) {
            num_commands++;
            commands[num_commands] = __strtok(NULL, ";");
        }

        for (c = 0; c < num_commands; c++) {
            /** Parse command into tokens */
            token = __strtok(commands[c], " ");
            i = 0;
            while (token != NULL)
            {
                args[i] = token;
                i++;
                token = __strtok(NULL, " ");
            }
            args[i] = NULL;

            /** Check for built-in commands */
            if (_strcmp(args[0], "cd") == 0)
            {
                execute_cd(args);
                continue;
            }
            else if (_strcmp(args[0], "exit") == 0)
            {
                execute_exit(args);
            }
            if (_strcmp(args[0], "printenv") == 0)
            {
                if (args[1] != NULL)
                {
                    execute_printenv(env, args[1]); /** Print only the value of a specific variable */
                }
                else
                {
                    execute_printenv(env, NULL); /** Print all environment variables */
                }
                continue;
            }
            if (_strncmp(args[0], "$", 1) == 0) {
                execute_printenv(env, args[0] + 1); /** Print the value of the variable */
                continue;
            }
            else if (_strcmp(args[0], "setenv") == 0)
            {
                execute_setenv(args);
                continue;
            }
            else if (_strcmp(args[0], "unsetenv") == 0)
            {
                execute_unsetenv(args);
                continue;
            }
	     else if (_strcmp(args[0], "echo") == 0)
            {
                /** Check for output redirection */
                for (i = 0; args[i] != NULL; i++)
                {
                    if (_strcmp(args[i], ">") == 0)
                    {
                        int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                        if (fd == -1)
                        {
                            perror("open");
                            exit(1);
                        }
                        if (dup2(fd, STDOUT_FILENO) == -1)
                        {
                            perror("dup2");
                            exit(1);
                        }
                        close(fd);
                        args[i] = NULL;
                        break;
                    }
                }
                execute_echo(args);
                continue;
            }

            /** checking first before fork*/
            filename = args[0];
            full_path = find_executable(filename, env);

            /** Fork and execute command */
            pid = fork();
            if (pid == 0)
            {
                /** Child process */
                chang = getppid();

                if (full_path != NULL)
                {
                    execve(full_path, args, env);
                    perror("execve");
                    exit(1);
                }
                else
                {
                    fprintf(stderr, "%s: command not found\n", args[0]);
                    exit(1);
                }
            }
            else if (pid < 0)
            {
                /** Error forking */
                perror("fork");
                exit(1);
            }
            else
            {
                /** Parent process */
                waitpid(pid, &status, 0);
            }
        }
    }

    free(input);
    return 0;
}
