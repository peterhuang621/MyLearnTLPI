#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
// #define LARGEFILE64_SOURCE
// #define FILE_OFFSET_BITS 64

int main(int argc, char const* argv[])
{
    int fd;
    __off64_t off;
    if (argc != 3 || strcmp(argv[1], "--help") == 0)usageErr("%s pathname offset\n", argv[0]);
    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        errExit("open64");
    }
    off = atoll(argv[2]);
    if (lseek64(fd, off, SEEK_SET) == -1) {
        errExit("lseek64")
    }
    if (write(fd, "test", 4) == -1) {
        errExut("write")
    }
    exit(EXIT_SUCCESS);
    return 0;
}
