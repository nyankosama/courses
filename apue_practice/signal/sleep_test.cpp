#include "apue.h"
#include <signal.h>

static void alarm_handler(int signal){
    printf("alarm interupt\n");
}

int main(){
    signal(SIGALRM, alarm_handler);
    printf("raise alarm 2 seconds\n");
    alarm(2);
    printf("sleep for 5 seconds\n");
    sleep(5);
}

