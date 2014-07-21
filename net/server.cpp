#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include "EchoServer.h"

int main(){
    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(9123);
    EchoServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}
