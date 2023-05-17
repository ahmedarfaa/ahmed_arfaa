#include "main.h"

/**
 * 
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
    else if (_strcmp(args[0], "printenv") == 0)
    {
        if (args[1] != NULL)
        {
            execute_printenv(env, args[1]); /** Print only the value of a specific variable */
        }
        else
        {
            execute_printenv(env, NULL); /** Print all environment variables */
        }
    }
    else if (_strncmp(args[0], "$", 1) == 0) {
        execute_printenv(env, args[0] + 1); /** Print the value of the variable */
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
        execute_echo(args, *status, env);
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
/**
 *
 *
 */
char *find_executable(char *filename, char **env)
{
    char *full_path = NULL;
    char *path_env = NULL;
    char *path = NULL;
    char *token = NULL;
    size_t path_len;
    size_t filename_len;
    int i;

    /** Check if filename is an absolute path or a relative path starting with "./"
    */
    if (filename[0] == '/')
    {
        if (access(filename, X_OK) == 0)
        {
            full_path = _strdup(filename);
            if (full_path == NULL)
            {
                perror("_strdup");
                exit(1);
            }
            return full_path;
        }
        else
        {
            return NULL;
        }
    }
    else if (_strncmp(filename, "./", 2) == 0)
    {
        if (access(filename + 2, X_OK) == 0)
        {
            full_path = _strdup(filename + 2);
            if (full_path == NULL)
            {
                perror("_strdup");
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
        if (_strncmp(env[i], "PATH=", 5) == 0)
        {
            path_env = env[i] + 5;
            break;
        }
    }

    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return NULL;
    }

    path = _strdup(path_env);
    if (path == NULL) {
        perror("_strdup");
        exit(1);
    }

    token = strtok(path, ":");
    while (token != NULL)
    {
        path_len = _strlen(token);
        filename_len = _strlen(filename);
        full_path = malloc(path_len + filename_len + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(1);
        }
        if (_snprintf(full_path, path_len + filename_len + 2, "%s/%s", token, filename) < 0)
        {
            /* Error or buffer overflow */
            return NULL;
        }
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
