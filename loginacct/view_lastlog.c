#include "../lib/tlpi_hdr.h"
#include "../users_groups/ugid_functions.h"
#include <fcntl.h>
#include <lastlog.h>
#include <paths.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    struct lastlog llog;
    int fd, j;
    uid_t uid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [username...]\n", argv[0]);

    fd = open(_PATH_LASTLOG, O_RDONLY);
    if (fd == -1)
        errExit("open");

    for (j = 1; j < argc; j++)
    {
        uid = userIdFromName(argv[j]);
        if (uid == -1)
        {
            printf("No such user: %s\n", argv[j]);
            continue;
        }

        if (lseek(fd, uid * sizeof(struct lastlog), SEEK_SET) == -1)
            errExit("lseek");

        if (read(fd, &llog, sizeof(struct lastlog)) <= 0)
        {
            printf("read failed for %s\n", argv[j]);
            continue;
        }

        printf("%-8.8s %-6.6s %-20.20s %s", argv[j], llog.ll_line, llog.ll_host, ctime((time_t *)&llog.ll_time));
    }
    close(fd);
    exit(EXIT_SUCCESS);
    return 0;
}
