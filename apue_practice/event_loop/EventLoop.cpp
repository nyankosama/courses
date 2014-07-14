#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "EventLoop.h"
#include "Singleton.h"

EventLoopMgr::EventLoopMgr() {
    events_ = new epoll_event[MAX_EVENTS];
    efd_ = epoll_create(1);
}

EventLoopMgr::~EventLoopMgr(){
    delete events_;
}

void EventLoopMgr::handleEvent() {
    int n;
    std::cout << "EPOLL_WAIT begins" << std::endl;
    n = epoll_wait(efd_, events_, MAX_EVENTS, -1);
    std::cout << "EPOLL_WAIT return" << std::endl;
    std::cout << "EPOLL_RETURN_N = " << n << std::endl;
    for (int i = 0; i < n; i++) {
        if ((events_[i].events & EPOLLERR) ||
                (events_[i].events & EPOLLHUP) ||
                (!(events_[i].events & EPOLLIN)))  {
            std::cerr << "epoll_wait error" << std::endl;
            abort();
        }

        std::shared_ptr<EventHandler> handler = handlerTable_[events_[i].data.fd]; 
        handler->handleEvent(EVENT_READ);
    }
    std::cout << "EPOLL_WAIT complete" << std::endl;
}

void EventLoopMgr::registerHandler(std::shared_ptr<EventHandler>& handler) {
    handlerTable_[handler->getSockfd()] = handler;
    int ret = epoll_ctl(efd_, EPOLL_CTL_ADD, handler->getSockfd(), &(handler->getEvent()));
    if (ret == -1) {
        std::cerr << "epoll_ctl_add error!" << std::endl;
        abort();
    }
}

void EventLoopMgr::removeHandler(int keyfd) {
    handlerTable_.erase(keyfd);
}

std::shared_ptr<EventHandler> EventHandlerFactory::createHandler(HandlerType type, int sockfd) {
    struct epoll_event event;
    switch (type) {
    case SOCKET_ACCEPTOR:
        event.events = EPOLLIN | EPOLLET;
        return std::shared_ptr<SocketAcceptor>(new SocketAcceptor(sockfd, event));
        break;
    case ECHO_HANDLER:
        event.events = EPOLLIN | EPOLLET;
        return std::shared_ptr<EchoHandler>(new EchoHandler(sockfd, event));
        break;
    }
    return NULL;
}

void SocketAcceptor::handleEvent(EventType type) {
    std::cout << "acceptor EPOLLIN" << std::endl;
    struct sockaddr clientAddr;
    socklen_t len = sizeof(clientAddr);
    int clientfd;

    clientfd = accept(sockfd_, &clientAddr, &len);
    std::cout << "client sockfd=" << clientfd << std::endl;
    int ret = makeSocketNonBlocking(clientfd);
    if (ret == -1) {
        std::cerr << "set non-blocking error!" << std::endl;
        abort();
    }

    std::shared_ptr<EventHandler> handler = Singleton<EventHandlerFactory>::instance().createHandler(ECHO_HANDLER, clientfd);
    Singleton<EventLoopMgr>::instance().registerHandler(handler);
    std::cout << "acceptor EPOLLIN complete!" << std::endl;
}

void EchoHandler::handleEvent(EventType type) {
    std::cout << "echo EPOLLIN" << std::endl;
    int n = 0;
    char buf[512];
    std::cout << "sockfd_ = " << sockfd_ << std::endl;
    while ((n = read(sockfd_, buf, sizeof(buf)) != 0)) {
        int ret = write(sockfd_, buf, n);
        if (ret == -1) {
            std::cerr << "echo write error!" << std::endl;
            abort();
        }
    }

    if (n == -1) {
        std::cerr << "echo read error!" << std::endl;
        abort();
    }
    
    std::cout << "echo EPOLLIN complete" << std::endl;
    Singleton<EventLoopMgr>::instance().removeHandler(sockfd_);
    close(sockfd_);
    std::cout << "echo EPOLLIN closed" << std::endl;
}

int makeSocketNonBlocking(int sfd) {
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1) {
        perror ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1) {
        perror ("fcntl");
        return -1;
    }

    return 0;
}
