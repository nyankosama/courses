#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "EventLoop.h"
#include "Singleton.h"


int main(){
    int sfd;
    int s_len;
    struct sockaddr_in serverAddr;
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(9123);
    s_len = sizeof(serverAddr);
    bind(sfd, (struct sockaddr *)&serverAddr, s_len);
    makeSocketNonBlocking(sfd);
    listen(sfd, 5);

    std::cout << "server sockfd =" << sfd << std::endl;
    
    EventLoopMgr& mgr = Singleton<EventLoopMgr>::instance();
    std::shared_ptr<EventHandler> acceptor = Singleton<EventHandlerFactory>::instance().createHandler(SOCKET_ACCEPTOR, sfd);
    mgr.registerHandler(acceptor);

    std::cout << "event loop begins!" << std::endl;
    while(1){
        mgr.handleEvent();
    }
    close(sfd);
}
