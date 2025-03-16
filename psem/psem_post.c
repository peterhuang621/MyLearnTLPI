#include "../lib/tlpi_hdr.h"
#include <semaphore.h>

int main(int argc, char const *argv[])
{
    sem_t *sem;
    if (argc != 2)
        usageErr("%s sem-name\n", argv[0]);

    sem = sem_open(argv[1], 0);
    if (sem == SEM_FAILED)
        errExit("sem_open");
    if (sem_post(sem) == -1)
        errExit("sem_post");
    exit(EXIT_SUCCESS);

    return 0;
}
