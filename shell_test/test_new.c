#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

void execute_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
}

void execute_exit()
{
    exit(0);
}

char *find_executable(char *filename, char **env)
{
    char *full_path = NULL;
    char *path_env = NULL;
    char *path = NULL;
    char *token = NULL;
    size_t path_len;
    size_t filename_len;
    int i;

    /** Check if filename is an absolute path
    */
    if (filename[0] == '/')
    {
        if (access(filename, X_OK) == 0)
        {
            full_path = strdup(filename);
            if (full_path == NULL)
            {
                perror("strdup");
                exit(1);
            }
            return full_path;
        }
        else
        {
            return NULL;
        }
    }

    /** Get the PATH environment variable
    */
    for (i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path_env = env[i] + 5;
            break;
        }
    }

    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return NULL;
    }

    path = strdup(path_env);
    if (path == NULL) {
        perror("strdup");
        exit(1);
    }

    token = strtok(path, ":");
    while (token != NULL)
    {
        path_len = strlen(token);
        filename_len = strlen(filename);
        full_path = malloc(path_len + filename_len + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(1);
        }
        snprintf(full_path, path_len + filename_len + 2, "%s/%s", token, filename);
        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return full_path;
        }
        free(full_path);
        token = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}
void execute_printenv(char **env, char *var)
{
    char *value;
    char **envp;

    /** If a variable is provided, print only its value
    */
    if (var != NULL)
    {
        value = getenv(var);
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
        /**Otherwise, print all environment variables
        */
        envp = env;
        while (*envp != NULL)
        {
            printf("%s\n", *envp);
            envp++;
        }
    }
}
void execute_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }
    if (setenv(args[1], args[2], 1) != 0)
    {
        perror("setenv");
    }
}

void execute_unsetenv(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }
    if (unsetenv(args[1]) != 0)
    {
        perror("unsetenv");
    }
}


int main(int __attribute__((unused)) argc, char ** __attribute__((unused)) argv, char **env)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read;
    char *args[64];
    int status;
    char *token;
    int i;
    pid_t pid;
    char *filename;
    char *full_path;
    (void) argv;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
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
            execute_exit();
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