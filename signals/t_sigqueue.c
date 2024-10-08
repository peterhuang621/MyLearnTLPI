#define _POSIX_C_SOURCE 199309
#include<signal.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/get_num.h"

int main(int argc, char const* argv[])
{
    int sig, numSigs, j, sigData;
    union sigval sv;

    if (argc < 4 || strcmp(argv[1], "--help") == 0)usageErr("%s pid sig-num data [num-sigs]\n", argv[0]);
    printf("%s: PID is %ld, UID is %ld\n", argv[0], (long)getpid(), (long)getuid());
    sig = getInt(argv[2], 0, "sig-num");
    sigData = getInt(argv[3], GN_ANY_BASE, "data");
    numSigs = (argc > 4) ? getInt(argv[4], GN_GT_0, "num-sigs") : 1;
    for (j = 0;j < numSigs;j++) {
        sv.sival_int = sigData + j;
        if (sigqueue(getLong(argv[1], 0, "pid"), sig, sv) == -1)errExit("sigqueue %d", j);
    }
    exit(EXIT_SUCCESS);
    return 0;
}
