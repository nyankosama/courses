#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("nyankosama")) == NULL) {
        printf("getpwnam(nyankosama) error");
    }
    alarm(1);
    printf("handle end");
}

int main() {
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for ( ; ; ) {
        if ((ptr = getpwnam("nyankosama")) == NULL)
            printf("getpwnam error");
        if (strcmp(ptr->pw_name, "nyankosama") != 0) {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
}



