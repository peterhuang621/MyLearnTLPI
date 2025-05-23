#define _BSD_SOURCE
#include "../lib/tlpi_hdr.h"
#include <sys/mman.h>

#define LEN (1024 * 1024)

#define SHELL_FMT "cat /proc/%lld/maps | grep zero"
#define CMD_SIZE (sizeof(SHELL_FMT) + 20)

int main(int argc, char const *argv[])
{
    char cmd[CMD_SIZE];
    char *addr;

    addr = mmap(NULL, LEN, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    printf("Before mprotect()\n");
    snprintf(cmd, CMD_SIZE, SHELL_FMT, (long long)getpid());
    system(cmd);

    if (mprotect(addr, LEN, PROT_READ | PROT_WRITE) == -1)
        errExit("mprotect");

    printf("After mprotect()\n");
    system(cmd);
    exit(EXIT_SUCCESS);
    return 0;
}
