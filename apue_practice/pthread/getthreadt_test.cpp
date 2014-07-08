#include "apue.h"
#include <pthread.h>

int main(){
    printf("pthread_t=%d\n", pthread_self());
}
