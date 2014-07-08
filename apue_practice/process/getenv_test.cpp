#include "apue.h"

int main(){
    char* val = getenv("USER");
    printf("%s\n", val);
}
