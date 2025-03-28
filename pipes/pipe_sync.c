#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include "../time/curr_time.h"
int main(int argc, char const *argv[])
{
    int pfd[2];
    int j, dummy;
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);
    setbuf(stdout, NULL);
    printf("%s Parent started\n", currTime("%T"));
    if (pipe(pfd) == -1)
        errExit("pipe");
    for (j = 1; j < argc; j++)
    {
        switch (fork())
        {
        case -1:
            errExit("fork %d", j);
            break;
        case 0:
            if (close(pfd[0]) == -1)
                errExit("close");
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
            printf("%s Child %d (PID=%lld) closing pipe\n", currTime("%T"), j, (long long)getpid());
            if (close(pfd[1]) == -1)
                errExit("close");
            _exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
    if (close(pfd[1]) == -1)
        errExit("close");

    if (read(pfd[0], &dummy, 1) != 0)
        fatal("parent didn't get EOF");
    printf("%s Parent ready to go\n", currTime("%T"));

    exit(EXIT_SUCCESS);
    return 0;
}
