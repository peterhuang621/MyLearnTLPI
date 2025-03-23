#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SV_SOCK_PATH "/tmp/ud_ucase"
#define BUF_SIZE 10