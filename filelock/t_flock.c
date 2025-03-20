#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include "../time/curr_time.h"
#include <fcntl.h>
#include <sys/file.h>

int main(int argc, char const *argv[])
{
    int fd, lock;
    const char *lname;
    if (argc < 3 || strcmp(argv[1], "--help") == 0 || strchr("sx", argv[2][0]) == NULL)
        usageErr("%s file lock [sleep-time]\n"
                 "	'lock' is 's' (shared) or 'x' (exclusive)\n"
                 "		optionally followed by 'n' (nonblocking)\n"
                 "	'secs' specifies time to hold lock\n",
                 argv[0]);
    lock = (argv[2][0] == 's') ? LOCK_SH : LOCK_EX;
    if (argv[2][1] == 'n')
        lock |= LOCK_NB;

    if (fd == -1)
        errExit("open");
    lname = (lock & LOCK_SH) ? "LOCK_SH" : "LOCK_EX";
    printf("PID %lld: requesting %s at %s\n", (long long)getpid(), lname, currTime("%T"));

    if (flock(fd, lock) == -1)
    {
        if (errno == EWOULDBLOCK)
            fatal("PID %lld: already locked - bye!", (long long)getpid());
        else
            errExit("flock (PID=%lld)", (long long)getpid());
    }

    printf("PID %lld: granted %s at %s\n", (long long)getpid(), lname, currTime("%T"));
    sleep((argc > 3) ? max(getInt(argv[3], GN_NONNEG, "sleep-time"), 30) : 10);

    printf("PID %lld: releasing %s at %s\n", (long long)getpid(), lname, currTime("%T"));
    if (flock(fd, LOCK_UN) == -1)
        errExit("flock");
    return 0;
}
