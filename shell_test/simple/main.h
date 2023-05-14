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

void execute_cd(char **args);
void execute_exit(char **args);
char *find_executable(char *filename, char **env);
void execute_printenv(char **env, char *var);
void execute_setenv(char **args);
void execute_unsetenv(char **args);
int _snprintf(char *str, size_t size, const char *format, ...);


#endif