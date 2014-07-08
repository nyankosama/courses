#include "apue.h"

int main(){
    printf("buf=%d\n", sysconf(_PC_PIPE_BUF));
}
