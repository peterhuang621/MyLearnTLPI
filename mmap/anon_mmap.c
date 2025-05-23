#ifdef USE_MAP_ANON
#define _BSD_SOURCE
#endif
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int *addr;
#ifdef USE_MAP_ANON
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
#else
    int fd;
    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    if (close(fd) == -1)
        errExit("close");
#endif
    *addr = 1;

    switch (fork())
    {
    case -1:
        errExit("fork");
        break;
    case 0:
        printf("Child started, value = %d\n", *addr);
        (*addr)++;
        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);
    default:
        if (wait(NULL) == -1)
            errExit("wait");
        printf("In parent, value = %d\n", *addr);
        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);
        break;
    }

    return 0;
}
