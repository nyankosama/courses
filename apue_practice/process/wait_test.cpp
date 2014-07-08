#include "apue.h"
#include <sys/wait.h>
#include <signal.h>

static void my_handler(int signal){
    //do nothing}
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: cmd process_num\n");
        exit(0);
    }

    struct sigaction act;
    act.sa_handler = my_handler;
    act.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);

    int process_num = atoi(argv[1]);
    for (int i = 0; i < process_num; i++) {
        int pid;
        if ((pid = fork()) < 0){
            printf("error fork!");
        }
        else if(pid == 0){
            printf("child process here, pid=%d\n", getpid()); 
            sleep(2);
            exit(0);
        }
    }

    /*for (int i = 0; i < process_num; i++){
        int return_pid;
        if ((return_pid = wait(NULL)) < 0){
            printf("error wait!");
        }
        printf("child process return, pid=%d\n", return_pid);
    }*/
    
    if (wait(NULL) == -1){
        printf("all child terminated\n");
    }

}

