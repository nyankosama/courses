#include "apue.h"
#include <pthread.h>


pthread_once_t initflag = PTHREAD_ONCE_INIT;

void thread_init(void){
    printf("pthread init\n");
}

void* thread_handler(void* arg){
    pthread_once(&initflag, thread_init);
    printf("thread handler\n");
    pthread_exit((void*)1);
}


int main(){
    printf("main start\n");
    pthread_t tid;
    for (int i = 0; i < 5; i++){
        pthread_create(&tid, NULL, thread_handler, (void*)0); 
    }
    printf("main sleep\n");
    sleep(5);
    printf("main exit\n");
    exit(0);
}

