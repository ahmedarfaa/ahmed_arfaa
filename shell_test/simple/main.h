#ifndef MAIN_H
#define MAIN_H

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
#include <fcntl.h>

#ifndef SIZE
#define SIZE 1024
#endif
extern char **environ;

void execute_cd(char **args);
void execute_exit(char **args);
char *find_executable(char *filename, char **env);
void execute_printenv(char **env, char *var);
void execute_setenv(char **args);
void execute_unsetenv(char **args);
int _snprintf(char *str, size_t size, const char *format, ...);
char *_memcpy(char *dest, const char *src, unsigned int n);
int _atoi(char *s);
size_t _strlen(const char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *s);
int _strcmp(char *s1, char *s2);
int _isupper(int c);
void _setenv(char ***envp, const char *name, const char *value);
char *__strtok(char *string, const char *cutter);
unsigned int _equal(char cut, const char *string);
char *_getenv(const char *name);
void execute_echo(char **args, int status, char **env);
void execute_command_with_redirection(char **args, char *full_path);
void execute_clear(void);
char *_strchr(char *s, char c);
int _sprintf(char *buf, const char *format, ...);

#endif
