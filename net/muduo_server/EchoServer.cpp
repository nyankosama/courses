#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <muduo/base/Logging.h>
#include "EchoServer.h"

EchoServer::EchoServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
    : loop_(loop),
      server_(loop, listenAddr, "EchoServer") {
    server_.setMessageCallback(
        boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::start() {
    server_.start();
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time) {
    muduo::string msg(buf->retrieveAllAsString());
    conn->send(msg);
}

