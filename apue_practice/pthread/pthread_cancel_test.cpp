#include "apue.h"
#include <pthread.h>

void* thread_handler(void*){
    printf("thread start \n");
    int sum = 0;
    for (int i = 0; i < 10000; i++){
        for (int k = 0; k < 10000; k++){
            sum += i * k;   
        } 
    }
    printf("thread test cancel");
    pthread_testcancel();
    printf("thread end\n");
    pthread_exit((void*)1);
}


int main(){
    pthread_t tid;
    printf("main start\n");
    pthread_create(&tid, NULL, thread_handler, (void*)1);
    sleep(1);
    printf("main cancel thread\n");
    pthread_cancel(tid);
    printf("main join thread\n");
    pthread_join(tid, NULL); 
    printf("main end\n");
    exit(0);
}
