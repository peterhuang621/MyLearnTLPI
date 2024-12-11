#define _GNU_SOURCE
#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <sched.h>

int main(int argc, char const *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid\n", argv[0]);
    pid_t pid = getInt(argv[1], GN_NONNEG, "pid");

    cpu_set_t set;
    int s = sched_getaffinity(pid, sizeof(cpu_set_t), &set);
    if (s == -1)
        errExit("sched_getaffinity");
    printf("CPUs:");
    for (int cpu = 0; cpu < CPU_SETSIZE; cpu++)
    {
        if (CPU_ISSET(cpu, &set))
            printf(" %d", cpu);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
    return 0;
}
