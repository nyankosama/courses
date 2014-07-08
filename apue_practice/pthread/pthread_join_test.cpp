#include "apue.h"
#include <pthread.h>

static void* thr_fn(void *arg){
    printf("thread:%d start!\n", arg);
    printf("thread:%d sleep 2 seconds\n", arg);
    sleep(2);
    printf("thread:%d return\n", arg);
    pthread_exit((void *)1);
}

int main(){
    pthread_t tid1;
    pthread_t tid2;
    void* ret;
    printf("main start!\n");
    pthread_create(&tid1, NULL, thr_fn, (void *)1);
    pthread_create(&tid2, NULL, thr_fn, (void *)2);
    printf("main create thread\n");
    printf("main sleep 5 seconds\n");
    sleep(5);
    printf("main join\n");
    pthread_join(tid1, &ret);
}
