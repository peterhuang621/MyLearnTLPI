#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include <sys/socket.h>
#include <sys/un.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100