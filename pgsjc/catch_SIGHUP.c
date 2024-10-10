#define _XOPEN_SOURCE 500
#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <signal.h>
#include <unistd.h>

static void handler(int sig)
{
}

int main(int argc, char const *argv[])
{
    pid_t childPid;
    struct sigaction sa;
    setbuf(stdout, NULL);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        errExit("sigaction");
    childPid = fork();
    if (childPid == -1)
        errExit("fork");
    if (childPid == 0 && argc > 1)
    {
        if (setpgid(0, 0) == -1)
            errExit("setpgid");
    }
    printf("PID=%lld; PPID=%lld; PGID=%lld; SID=%lld\n", (long long)getpid(), (long long)getppid(),
           (long long)getpgrp(), (long long)getsid(0));
    alarm(60);
    for (;;)
    {
        pause();
        printf("%lld: caught SIGHUP\n", (long long)getpid());
    }
    return 0;
}