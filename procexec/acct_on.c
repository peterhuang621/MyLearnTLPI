#define _BSD_SOURCE
#include <unistd.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char const* argv[])
{
    if (argc > 2 || (argc > 1 && strcmp(argv[1], "--help") == 0))usageErr("%s [file]\n");
    if (acct(argv[1]) == -1)errExit("acct");
    printf("Process accounting %s\n", (argv[1] == NULL) ? "disabled" : "enabled");
    exit(EXIT_SUCCESS);
    return 0;
}
