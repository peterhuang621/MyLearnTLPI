#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <getopt.h>
#include <mqueue.h>

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-n] name\n", progName);
    fprintf(stderr, "		-n		Use O_NONBLOCK flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    int flags, opt;
    mqd_t mqd;
    unsigned int prio;
    void *buffer;
    struct mq_attr attr;
    ssize_t numRead;

    flags = O_RDONLY;
    while ((opt = getopt(argc, argv, "n")) != -1)
    {
        switch (opt)
        {
        case 'n':
            flags |= O_NONBLOCK;
            break;
        default:
            usageError(argv[0]);
            break;
        }
    }
    if (optind >= argc)
        usageError(argv[0]);

    mqd = mq_open(argv[optind], flags);
    if (mqd == (mqd_t)-1)
        errExit("mq_open");
    if (mq_getattr(mqd, &attr) == -1)
        errExit("mq_getattr");
    buffer = malloc(attr.mq_msgsize);
    if (buffer == NULL)
        errExit("malloc");

    numRead = mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
    if (numRead == -1)
        errExit("mq_receive");
    printf("Read %lld bytes; priority = %u\n", (long long)numRead, prio);
    if (write(STDOUT_FILENO, buffer, numRead) == -1)
        errExit("write");
    write(STDOUT_FILENO, "\n", 1);
    exit(EXIT_SUCCESS);
    return 0;
}
