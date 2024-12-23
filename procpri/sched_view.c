#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <sched.h>

int main(int argc, char const *argv[])
{
    int j, pol;
    struct sched_param sp;
    for (j = 1; j < argc; j++)
    {
        pol = sched_getscheduler(getLong(argv[j], 0, "pid"));
        if (pol == -1)
            errExit("sched_getscheduler");
        if (sched_getparam(getLong(argv[j], 0, "pid"), &sp) == -1)
            errExit("sched_getparam");
        printf("%s: %-5s %2d\n", argv[j],
               (pol == SCHED_OTHER)  ? "OTHER"
               : (pol == SCHED_RR)   ? "RR"
               : (pol == SCHED_FIFO) ? "FIFO"
               :
#ifdef SCHED_BATCH
               (pol == SCHED_BATCH) ? "BATCH"
               :
#endif
#ifdef SCHED_IDLE
               (pol == SCHED_IDLE) ? "IDLE"
                                   :
#endif
                                   "???",
               sp.sched_priority);
    }
    exit(EXIT_SUCCESS);
    return 0;
}
