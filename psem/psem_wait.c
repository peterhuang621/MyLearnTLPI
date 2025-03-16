#include "../lib/tlpi_hdr.h"
#include <semaphore.h>

int main(int argc, char const *argv[])
{
    sem_t *sem;
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sem-name\n", argv[0]);
    sem = sem_open(argv[1], 0);
    if (sem == SEM_FAILED)
        errExit("sem_open");
    if (sem_wait(sem) == -1)
        errExit("sem_wait");
    printf("%lld sem_wait() succeeded\n", (long long)getpid());
    exit(EXIT_SUCCESS);

    return 0;
}
