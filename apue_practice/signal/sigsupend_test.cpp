#include "apue.h"
#include <signal.h>

static void int_handler(int signal){
    printf("main terminated\n");
    exit(0);
}

int main(){
    sigset_t newmask, oldmask;
    signal(SIGINT, int_handler);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    printf("sleep 5 seconds\n");
    sleep(5);
    printf("reset mask and pause\n");
    sigsuspend(&oldmask);
}
