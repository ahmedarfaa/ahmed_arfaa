#include "main.h"

/**
 *
 *
 */
void execute_echo(char **args)
{
    int i, fd;
    bool redirect_output = false;
    int stdout_fd = dup(STDOUT_FILENO);

    for (i = 1; args[i] != NULL; i++)
    {
        if (_strcmp(args[i], ">") == 0)
        {
            redirect_output = true;
            fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
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

    for (i = 1; args[i] != NULL; i++)
    {
        if (i > 1)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        if (args[i][0] == '"' || args[i][0] == '\'')
        {
            char *end_quote = strchr(args[i] + 1, args[i][0]);
            if (end_quote != NULL)
            {
                write(STDOUT_FILENO, args[i] + 1, end_quote - args[i] - 1);
            }
            else
            {
                write(STDOUT_FILENO, args[i] + 1, _strlen(args[i]) - 1);
            }
        }
        else if (args[i][0] == '$')
        {
            char *value = getenv(args[i] + 1);
            if (value != NULL)
            {
                write(STDOUT_FILENO, value, _strlen(value));
            }
        }
	else if (args[i][0] == '$' && args[i][1] == '$')
        {
            pid_t value = getpid();
            if (value >= 0)
            {
                printf("%d", value);
            }
        }
        else
        {
            write(STDOUT_FILENO, args[i], _strlen(args[i]));
        }
    }

    if (redirect_output)
    {
        if (dup2(stdout_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(stdout_fd);
    }
}
/**
 *
 */

char *_getenv(const char *name)
{
    char **env = environ;
    size_t name_len = strlen(name);

    while (*env != NULL)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            return *env + name_len + 1;
        }
        env++;
    }

    return NULL;
}
/**
 *
 */

void execute_cd(char **args)
{
	char *home = _getenv("HOME");
    if (args[1] == NULL)
    {
        chdir(home);
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
}

/**
 *
 */

void execute_printenv(char **env, char *var)
{
    char *value;
    char **envp;

    /** If a variable is provided, print only its value
    */
    if (var != NULL)
    {
        value = _getenv(var);
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

/**
 *
 *
 */

void _setenv(char ***envp, const char *name, const char *value) {
    int name_len, value_len, total_len, i;
    char *new_env, **new_environ;

    if (name == NULL || value == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }

    name_len = _strlen(name);
    value_len = _strlen(value);
    total_len = name_len + value_len + 2;

    new_env = malloc(total_len);
    if (new_env == NULL) {
        perror("malloc");
        return;
    }

    _snprintf(new_env, total_len, "%s=%s", name, value);

    for (i = 0; (*envp)[i] != NULL; i++) {
        if (_strncmp((*envp)[i], name, name_len) == 0 && (*envp)[i][name_len] == '=') {
            free((*envp)[i]);
            (*envp)[i] = new_env;
            return;
        }
    }

    new_environ = malloc((i + 2) * sizeof(char *));
    if (new_environ == NULL) {
        perror("malloc");
        free(new_env);
        return;
    }

    for (i = 0; (*envp)[i] != NULL; i++) {
        new_environ[i] = (*envp)[i];
    }

    new_environ[i] = new_env;
    new_environ[i + 1] = NULL;
    *envp = new_environ;
}

void execute_setenv(char **args) {
    _setenv(&environ, args[1], args[2]);
}

/**
 *
 */

void execute_unsetenv(char **args)
{
    int name_len, i, j;

    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    name_len = _strlen(args[1]);

    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(environ[i], args[1], name_len) == 0 && environ[i][name_len] == '=') {
            free(environ[i]);
            for (j = i; environ[j] != NULL; j++)
	    {
                environ[j] = environ[j + 1];
            }
            return;
        }
    }

    fprintf(stderr, "Variable %s not found\n", args[1]);
}

/**
 *
 *
 */
void execute_exit(char **args)
{
    if (args[1] != NULL)
    {
        int exit_code = atoi(args[1]);
        exit(exit_code);
    }
    else
    {
       exit (0);
    }
}
