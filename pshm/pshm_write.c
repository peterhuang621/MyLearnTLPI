#define _GNU_SOURCE
#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fd;
    size_t len;
    char *addr;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s shm-name string\n", argv[0]);

    fd = shm_open(argv[1], O_RDWR, 0);
    if (fd == -1)
        errExit("shm_open");
    len = strlen(argv[2]);

    if (ftruncate(fd, len) == -1)
        errExit("ftruncate");
    printf("Resized to %lld bytes\n", (long long)len);

    addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    if (close(fd) == -1)
        errExit("close");
    printf("copying %lld bytes\n", (long long)len);
    memcpy(addr, argv[2], len);

    exit(EXIT_SUCCESS);
    return 0;
}
