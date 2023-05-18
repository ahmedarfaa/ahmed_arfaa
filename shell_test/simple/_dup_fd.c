#include "main.h"

int _dup(int oldfd)
{
    int newfd;

    for (newfd = 0; newfd < 256; newfd++)
    {
        if (fcntl(newfd, F_GETFD) == -1)
        {
            break;
        }
    }

    if (dup2(oldfd, newfd) == -1)
    {
        perror("dup2");
        exit(1);
    }

    return newfd;
}
