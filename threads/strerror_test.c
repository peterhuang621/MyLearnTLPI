#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

extern char *mystrerror(int err);

static void *threadFunc(void *arg)
{
    char *str;
    printf("Other thread about to call strerror()\n");
    str = mystrerror(EPERM);
    printf("Other thread: str(%p) = %s\n", str, str);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t t;
    int s;
    char *str;
    str = mystrerror(EINVAL);
    printf("Main thread has called strerror()\n");

    s = pthread_create(&t, NULL, threadFunc, NULL);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_join(t, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    printf("Main thread: str (%p) = %s\n", str, str);
    exit(EXIT_SUCCESS);
    return 0;
}
