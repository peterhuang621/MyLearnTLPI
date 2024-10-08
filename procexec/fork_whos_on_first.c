#include<sys/wait.h>
#include"../lib/tlpi_hdr.h"
#include"../lib/get_num.h"

int main(int argc, char const* argv[])
{
    int numChildren, j;
    pid_t childPid;
    if (argc > 1 && strcmp(argv[1], "--help") == 0)usageErr("%s [num-children]\n", argv[0]);

    numChildren = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-children") : 1;

    setbuf(stdout, NULL);
    for (j = 0;j < numChildren;j++) {
        switch (childPid = fork())
        {
        case -1:
            errExit("fork");
            break;
        case 0:
            printf("%d child\n", j);
            _exit(EXIT_SUCCESS);
        default:
            printf("%d parent\n", j);
            wait(NULL);
            break;
        }
    }
    exit(EXIT_SUCCESS);
    return 0;
}
