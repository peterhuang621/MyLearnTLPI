#define _GNU_SOURCE
#include "../lib/tlpi_hdr.h"
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>

static void sigwinchHandler(int sig)
{
}

int main(int argc, char const *argv[])
{
    struct winsize ws;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigwinchHandler;
    if (sigaction(SIGWINCH, &sa, NULL) == -1)
        errExit("sigaction");

    for (;;)
    {
        pause();
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
            errExit("ioctl");
        printf("Caught SIGWINCH, new windown size: %d rows * %d columns\n", ws.ws_row, ws.ws_col);
    }

    return 0;
}
