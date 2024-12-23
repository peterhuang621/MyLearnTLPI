#define _GNU_SOURCE
#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <signal.h>
#include <string.h>

static int cmdNum;

static void handler(int sig)
{
    if (getpid() == getpgrp())
        fprintf(stderr, "Terminal FG process group: %lld\n", (long long)tcgetpgrp(STDERR_FILENO));
    fprintf(stderr, "Prcess %lld (%d) received signal %d (%s)\n", (long long)getpid(), cmdNum, sig, strsignal(sig));
    if (sig == SIGTSTP)
        raise(SIGSTOP);
}

int main(int argc, char const *argv[])
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGCONT, &sa, NULL) == -1)
        errExit("sigaction");

    if (isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Terminal FG process group: %lld\n", (long long)tcgetpgrp(STDIN_FILENO));
        fprintf(stderr, "Command		PID		PPID	PGRP	SID\n");
        cmdNum = 0;
    }
    else
    {
        if (read(STDIN_FILENO, &cmdNum, sizeof(cmdNum)) <= 0)
            fatal("read got EOF or error");
    }
    cmdNum++;
    fprintf(stderr, "%4d		%5lld	%5lld	%5lld	%5lld\n", cmdNum, (long long)getpid(), (long long)getppid(),
            (long long)getpgrp(), (long long)getsid(0));
    if (!isatty(STDIN_FILENO))
    {
        if (write(STDOUT_FILENO, &cmdNum, sizeof(cmdNum)) == -1)
            errMsg("write");
    }
    for (;;)
        pause();

    return 0;
}
