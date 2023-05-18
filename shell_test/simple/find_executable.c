#include "main.h"


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
