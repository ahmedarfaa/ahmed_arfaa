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
    int i;
    pid_t pid;
    char *filename;
    char *full_path;
    bool from_pipe = false;
    (void) argv;


    while (1 && !from_pipe)
    {
        write(STDOUT_FILENO, "$ ", 2);
        if (isatty(STDOUT_FILENO) == 0)
            from_pipe = true;
        if ((read = getline(&input, &input_size, stdin)) == -1)
        {
            perror("getline");
            exit(1);
        }
        if (input[read - 1] == '\n')
        {
            input[read - 1] = '\0';
        }

        /** Parse input into tokens
        */
        token = strtok(input, " ");
        i = 0;
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /** Check for built-in commands
        */
        if (strcmp(args[0], "cd") == 0)
        {
            execute_cd(args);
            continue;
        }
        else if (strcmp(args[0], "exit") == 0)
        {
            execute_exit(args);
        }
        if (strcmp(args[0], "printenv") == 0)
        {
            if (args[1] != NULL)
            {
                execute_printenv(env, args[1]); /** Print only the value of a specific variable
            */
            }
            else
            {
                execute_printenv(env, NULL); /** Print all environment variables
            */
            }
            continue;
        }
        else if (strcmp(args[0], "setenv") == 0)
        {
            execute_setenv(args);
            continue;
        }
        else if (strcmp(args[0], "unsetenv") == 0)
        {
            execute_unsetenv(args);
            continue;
        }

        /** Fork and execute command */
        pid = fork();
        if (pid == 0)
        {
            /** Child process */

            filename = args[0];
            full_path = find_executable(filename, env);
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

    free(input);
    return 0;
}
