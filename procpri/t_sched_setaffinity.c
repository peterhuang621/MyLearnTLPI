#define _GNU_SOURCE
#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <sched.h>

int main(int argc, char const *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid mask\n", argv[0]);
    pid_t pid = getInt(argv[1], GN_NONNEG, "pid");
    unsigned long mask = getLong(argv[2], GN_ANY_BASE, "octal-mask");

    cpu_set_t set;
    CPU_ZERO(&set);

    for (int cpu = 0; mask > 0; cpu++, mask >>= 1)
    {
        if (mask & 1)
            CPU_SET(cpu, &set);
    }
    if (sched_setaffinity(pid, sizeof(set), &set) == -1)
        errExit("sched_setaffinity");
    exit(EXIT_SUCCESS);
    return 0;
}
