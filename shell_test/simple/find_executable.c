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
