#ifndef _ECHOSERVER_H_
#define _ECHOSERVER_H_
#include <muduo/net/TcpServer.h>

class EchoServer {
public:
    EchoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);
    void start();

private:
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time);

    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;
};

#endif
