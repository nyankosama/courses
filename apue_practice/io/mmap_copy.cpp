#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;

    if (argc != 3){
        printf("usage: %s <fromfile> <tofile>\n", argv[0]);
        exit(1);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0){
        printf("fdin open error\n");
        exit(1);
    }
    
    
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){
        printf("fdout open error\n");
        exit(1);
    }

    if ((fstat(fdin, &statbuf)) < 0){
        printf("fstat error\n");
        exit(1);
    }

    lseek(fdout, statbuf.st_size - 1, SEEK_SET);
    if (write(fdout, "", 1) != 1){
        printf("write test error\n");
        exit(1);
    }

    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);

    memcpy(dst, src, statbuf.st_size); 
    printf("done, copy size=%d\n", (int)statbuf.st_size);
    exit(0);
}
