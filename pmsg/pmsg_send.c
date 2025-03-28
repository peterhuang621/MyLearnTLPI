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

    flags = O_WRONLY;
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
    if (optind + 1 >= argc)
        usageError(argv[0]);

    mqd = mq_open(argv[optind], flags);
    if (mqd == (mqd_t)-1)
        errExit("mq_open");

    prio = (argc > optind + 2) ? atoi(argv[optind + 2]) : 0;

    if (mq_send(mqd, argv[optind + 1], strlen(argv[optind + 1]), prio) == -1)
        errExit("mq_send");
    exit(EXIT_SUCCESS);
    return 0;
}
