#define _GNU_SOURCE
#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <signal.h>
#include <string.h>

static void handler(int sig)
{
    printf("PID=%lld: caught signal %d (%s)\n", (long long)getpid(), sig, strsignal(sig));
}

int main(int argc, char const *argv[])
{
    int j;
    struct sigaction sa;
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s {s|p} ...\n", argv[0]);
    setbuf(stdout, NULL);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGCONT, &sa, NULL) == -1)
        errExit("sigaction");
    printf("parent: PID=%lld, PPID=%lld, PGID=%lld, SID=%lld\n", (long long)getpid(), (long long)getppid(),
           (long long)getpgrp(), (long long)getsid(0));

    for (j = 1; j < argc; j++)
    {
        switch (fork())
        {
        case -1:
            errExit("fork");
        case 0:
            printf("child: PID=%lld, PPID=%lld, PGID=%lld, SID=%lld\n", (long long)getpid(), (long long)getppid(),
                   (long long)getpgrp(), (long long)getsid(0));
            if (argv[j][0] == 's')
            {
                printf("PID=%lld stopping\n", (long long)getpid());
                raise(SIGSTOP);
            }
            else
            {
                alarm(60);
                printf("PID=%lld pausing\n", (long long)getpid());
                pause();
            }
            _exit(EXIT_SUCCESS);

        default:
            break;
        }
    }
    sleep(3);
    printf("parent exiting\n");
    exit(EXIT_SUCCESS);
    return 0;
}
