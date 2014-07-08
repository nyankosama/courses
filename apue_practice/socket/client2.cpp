#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9123);
    len = sizeof(address);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1) {
        perror("error: client");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);

    return 0;
}


