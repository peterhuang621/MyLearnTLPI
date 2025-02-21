#include "../lib/error_functions.h"
#include "../lib/tlpi_hdr.h"
#include <dlfcn.h>

int main(int argc, char const *argv[])
{
    void *libHandle;
    void (*funcp)(void);
    const char *err;
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s lib-path func-name\n", argv[0]);

    libHandle = dlopen(argv[1], RTLD_LAZY);
    if (libHandle == NULL)
        fatal("dlopen: %s", dlerror());

    (void)dlerror();
    *(void **)(&funcp) = dlsym(libHandle, argv[2]);

    err = dlerror();
    if (err != NULL)
        fatal("dlsym: %s", err);

    if (funcp == NULL)
        printf("%s is NULL\n", argv[2]);
    else
        (*funcp)();

    exit(EXIT_SUCCESS);

    return 0;
}
