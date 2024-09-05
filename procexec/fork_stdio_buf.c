#include"../lib/tlpi_hdr.h"

int main(int argc, char const* argv[])
{
    printf("Hello world!\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    if (fork() == -1)errExit("fork");

    return 0;
}
