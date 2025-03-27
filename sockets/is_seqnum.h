#define _BSD_SOURCE
#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include "read_line.h"
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>

#define PORT_NUM "50000"
#define INT_LEN 30
