/*======================================================
    > File Name: eventLoop.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 22时31分17秒
 =======================================================*/
#include "event_loop.h"
#include "epoll.h"
#include "connection.h"
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
using namespace netlib;

EventLoop::EventLoop(int eventFd)
    :eventFd_(eventFd),epoll_(new Epoll(1024)),
    objectPool_(1024,0,epoll_)
{
    //将eventFd_添加到epoll事件表中
    epoll_->addFd(eventFd_);
}

EventLoop::~EventLoop()
{
    close(eventFd_);
}

void EventLoop::loop()
{
    while(1)
    {
        int count = epoll_->wait(events_);
        int sockfd;
        for(int i = 0; i < count ; i++)
        {
            sockfd = events_[i].data.fd;
            if(sockfd == eventFd_)  //有新的连接到来
            {
                handleEventFdRead();   
            }
            else if(events_[i].events & EPOLLRDHUP)
            {
                //处理关闭
                handleClose(events_[i].data.fd);
            }
            else if(events_[i].events & EPOLLIN)
            {
                //处理读事件
                handleRead(events_[i].data.fd);   
            }
            else if(events_[i].events & EPOLLOUT)
            {
                //处理可写
            }
            else if(events_[i].events & EPOLLERR)
            {
                //处理错误   
            }
        }
        
    }
}

void EventLoop::handleEventFdRead(void)
{
    uint64_t fd;    //用于保存新连接的fd
    ssize_t count = read(eventFd_,&fd,sizeof(fd));
    assert(count == sizeof(fd));
    //将新来的套接字添加进epoll事件表中
    epoll_->addFd((int)fd);
    //从连接池中取出新连接,并给智能指针自定义删除器，将连接放回连接池
    std::shared_ptr<Connection> connectionPtr(objectPool_.getObject(),[](Connection *p)[objectPool_.giveBackObject(p)]);
    connectionPtr->fd_ = fd;
    connectionMap_.insert(std::pair<int,std::shared_ptr<Connection>>(fd,connectionPtr));
}

void EventLoop::handleRead(int fd)
{
    int count = connectionMap_[fd]->inputBuffer_.readFromFd(fd);  //将数据读到该描述符的inputBuffer中
    
    messageCallback_(connectionMap_[fd],&connectionMap_[fd]->inputBuffer_);//当消息条件满足时调用messageCallback
    if(count == 0)  //对端关闭
    {
        handleClose(fd);
    }
}

void EventLoop::handleClose(int fd)
{
    close(fd);
    printf("已关闭\n");
    closeCallback_(connectionMap_[fd]);   
}


