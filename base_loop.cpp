/*======================================================
    > File Name: base_loop.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 13时59分48秒
 =======================================================*/
#include "base_loop.h"
#include <string>
#include "event_loop_thread_pool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <memory>

using namespace netlib;

BaseLoop::BaseLoop(std::string ip,int port,int loopNumber)
    :ip_(ip),
    port_(port),
    loopThreadPoolPtr_(std::make_shared<LoopThreadPool>(loopNumber))
{
}

BaseLoop::~BaseLoop()
{
    close(listenFd_);
}

int BaseLoop::createListenFd(void)
{

    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip_.c_str(),&address.sin_addr);
    address.sin_port = htons(port_);

    int sock = socket(PF_INET,SOCK_STREAM,0);
    assert(sock >= 0);
    
    int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
    assert(ret == 0);

    ret = listen(sock,100);
    assert(ret == 0);

    return sock; 
}


void BaseLoop::start(void)
{
    struct sockaddr_in clientAddress;   //保存客户端地址
    socklen_t len = sizeof(clientAddress); //客户端地址长度
    int connfd;
    listenFd_ = createListenFd();       //获得监听套接字
    loopThreadPoolPtr_->setMessageCallback(messageCallback_);   //设置读回调函数
    loopThreadPoolPtr_->setCloseCallback(closeCallback_);  //设置关闭回调函数
    loopThreadPoolPtr_->setWriteCompleteCallback(writeCompleteCallback_);
    loopThreadPoolPtr_->start();        //开启loop线程池

    while(1)
    {
        connfd = accept(listenFd_,(struct sockaddr *)&clientAddress,&len);
        connectionHandle(connfd);
    }   
}


void BaseLoop::connectionHandle(int connfd)
{
    int fd = loopThreadPoolPtr_->getNextLoop();
    uint64_t buff = connfd;
    int ret = write(fd,&buff,sizeof(buff));     //添加到指定的loop循环中
    assert(ret == sizeof(buff));
    //下面可以加入用户自定义的连接回调  
}
