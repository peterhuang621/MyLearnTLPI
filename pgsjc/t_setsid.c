#define _XOPEN_SOURCE 500
#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (fork() != 0)
        _exit(EXIT_SUCCESS);
    if (setsid() == -1)
        errExit("setsid");
    printf("PID=%lld, PGID=%lld, SID=%lld\n", (long long)getpid(), (long long)getpgrp(), (long long)getsid(0));
    if (open("/dev/tty", O_RDWR) == -1)
        errExit("open /dev/tty");
    exit(EXIT_SUCCESS);
    return 0;
}
