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

#ifndef SIZE
#define SIZE 64
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
char *_memcpy2(char **dest, char **src, unsigned int n);

#endif
