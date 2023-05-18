#include "main.h"

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
