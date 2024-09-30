#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <string.h>
#define MAX_ERROR_LEN 256

// _sys_nerr and _sys_errlist have been aborted in nowadays kernel.
static char buf[MAX_ERROR_LEN];

char *mystrerror(int err)
{
    if (err < 0 || strerror(err) == NULL)
    {
        snprintf(buf, MAX_ERROR_LEN, "Unknow error %d", err);
    }
    else
    {
        strncpy(buf, strerror(err), MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0';
    }
    return buf;
}