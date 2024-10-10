#define _GNU_SOURCE
#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <signal.h>
#include <string.h>

static void handler(int sig)
{
    printf("PID %lld: caught signal %2d (%s)\n", (long long)getpid(), sig, strsignal(sig));
}

int main(int argc, char const *argv[])
{
    pid_t parentPid, childPid;
    int j;
    struct sigaction sa;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s {d|s}... [ > sig.log 2>&1 ]\n", argv[0]);
    setbuf(stdout, NULL);
    parentPid = getpid();
    printf("PID of patrent process is:	%lld\n", (long long)parentPid);
    printf("Foreground process group ID is: %lld\n", (long long)tcgetpgrp(STDIN_FILENO));
    return 0;
}
