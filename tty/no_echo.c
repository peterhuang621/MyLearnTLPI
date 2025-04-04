#include "../lib/tlpi_hdr.h"
#include <termios.h>

#define BUF_SIZE 100

int main(int argc, char const *argv[])
{
    struct termios tp, save;
    char buf[BUF_SIZE];

    if (tcgetattr(STDIN_FILENO, &tp) == -1)
        errExit("tcgetattr");
    save = tp;
    tp.c_lflag &= (~ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
        errExit("tcsetattr");

    printf("Enter text: ");
    fflush(stdout);
    if (fgets(buf, BUF_SIZE, stdin) == NULL)
        printf("Got end-of-file/error on fgets()\n");
    else
        printf("\nRead: %s", buf);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &save) == -1)
        errExit("tcsetattr");

    exit(EXIT_SUCCESS);
    return 0;
}
