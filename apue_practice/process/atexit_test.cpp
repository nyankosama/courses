#include "apue.h"


static void my_exit1(){
    printf("my exit1\n");
}

static void my_exit2(){
    printf("my exit2\n");
}

int main(){
    atexit(my_exit1); 
    atexit(my_exit2); 
    printf("main is doen!\n");
    exit(0);
}
