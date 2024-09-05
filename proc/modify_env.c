#include <stdlib.h>
#include "../lib/tlpi_hdr.h"
#define _GNU_SOURCE

extern char** environ;

int main(int argc, char* argv[])
{
    int j;
    char** ep;
    clearenv();

    for (j = 1; j < argc; j++)
    {
        if (putenv(argv[j]) != 0)
        {
            errExit("putenv: %s", argv[j]);
        }
    }
    if (setenv("GREET", "Hello world", 0) == -1)
    {
        errExit("setenv");
    }
    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ep++)
    {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
    return 0;
}
