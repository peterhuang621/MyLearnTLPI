#include <signal.h>
typedef void (*__sighandler_t)(int);

__sighandler_t signal(int sig, __sighandler_t handler) {
    struct sigaction newDisp, preDisp;
    newDisp.sa_handler = handler;
    sigemptyset(&newDisp.sa_mask);
#ifdef OLD_SIGNAL
    newDisp.sa_flags = SA_RESETHAND | SA_NODEFER;
#else 
    newDisp.sa_flags = SA_RESTART;
#endif
    if (sigaction(sig, &newDisp, &preDisp) == -1)return SIG_ERR;
    else { return prevDisp.sa_handler; }
}
