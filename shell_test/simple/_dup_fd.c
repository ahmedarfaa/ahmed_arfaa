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

/**
 *
 */

int _dup2(int oldfd, int newfd)
{
    int tmpfd;

    if (oldfd == newfd)
    {
        return newfd;
    }

    tmpfd = fcntl(oldfd, F_DUPFD, newfd);
    if (tmpfd == -1)
    {
        perror("fcntl");
        exit(1);
    }

    if (tmpfd != oldfd && close(oldfd) == -1)
    {
        perror("close");
        exit(1);
    }

    return tmpfd;
}
