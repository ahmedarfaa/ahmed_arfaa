#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef SIZE
#define SIZE 1024
#endif

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

void execute_exit(char **args)
{
    int status = 0;

    if (args[1] != NULL)
    {
        status = atoi(args[1]);
    }

    exit(status);
}
int _snprintf(char *str, size_t size, const char *format, ...)
{
    va_list args;
    int len = 0;
    char *p = str;
    const char *fmt = format;

    va_start(args, format);

    while (*fmt != '\0' && len < (int)size - 1)
    {
        if (*fmt == '%')
        {
            /* Handle format specifier */
            fmt++;
            switch (*fmt)
            {
                case 's':
                {
                    char *s = va_arg(args, char *);
                    while (*s != '\0' && len < (int)size - 1)
                    {
                        *p++ = *s++;
                        len++;
                    }
                    break;
                }
                case 'd':
                {
                    int d = va_arg(args, int);
                    char buf[32];
                    int n = snprintf(buf, sizeof(buf), "%d", d);
                    if (n < 0 || len + n >= (int)size)
                    {
                        /* Error or buffer overflow */
                        va_end(args);
                        return -1;
                    }
                    memcpy(p, buf, n);
                    p += n;
                    len += n;
                    break;
                }
                /* Handle other format specifiers as needed */
                default:
                    /* Unsupported format specifier */
                    va_end(args);
                    return -1;
            }
        }
        else
        {
            /* Handle regular character */
            *p++ = *fmt;
            len++;
        }
        fmt++;
    }

    va_end(args);

    /* Null-terminate the string */
    *p = '\0';

    return len;
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

    /** Check if filename is an absolute path or a relative path starting with "./"
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
    else if (strncmp(filename, "./", 2) == 0)
    {
        if (access(filename + 2, X_OK) == 0)
        {
            full_path = strdup(filename + 2);
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

extern char **environ;

void _setenv(char ***envp, const char *name, const char *value) {
    int name_len, value_len, total_len, i;
    char *new_env, **new_environ;

    if (name == NULL || value == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }

    name_len = strlen(name);
    value_len = strlen(value);
    total_len = name_len + value_len + 2;

    new_env = malloc(total_len);
    if (new_env == NULL) {
        perror("malloc");
        return;
    }

    snprintf(new_env, total_len, "%s=%s", name, value);

    for (i = 0; (*envp)[i] != NULL; i++) {
        if (strncmp((*envp)[i], name, name_len) == 0 && (*envp)[i][name_len] == '=') {
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


void execute_unsetenv(char **args) {
    int name_len, i, j;

    if (args[1] == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    name_len = strlen(args[1]);

    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], args[1], name_len) == 0 && environ[i][name_len] == '=') {
            free(environ[i]);
            for (j = i; environ[j] != NULL; j++) {
                environ[j] = environ[j + 1];
            }
            return;
        }
    }

    fprintf(stderr, "Variable %s not found\n", args[1]);
}


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
    pid_t original = getppid();
    pid_t chang = getppid();
    int num_commands;
    char *commands[SIZE / 2 + 1];
    (void) argv;

    

    while (1 && !from_pipe)
    {
        
       if (chang == original)
        {
            write(STDOUT_FILENO, " ($) ", 5);
            
        }
        else if (chang != original)
        {
            write(STDOUT_FILENO, "$ ", 2);
        }
        if (isatty(STDOUT_FILENO) == 0)
            from_pipe = true;
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
        /** Parse input into tokens
        */
        /** Split input into commands */
        num_commands = 0;
        commands[num_commands] = strtok(input, ";");
        while (commands[num_commands] != NULL) {
            num_commands++;
            commands[num_commands] = strtok(NULL, ";");
        }

        for (c = 0; c < num_commands; c++) {
            /** Parse command into tokens */
            token = strtok(commands[c], " ");
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
        if (isupper(args[0][0]) || strncmp(args[0], "$", 1) == 0) {
            execute_printenv(env, args[0] + 1); /** Print the value of the variable */
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