/*======================================================
    > File Name: eventLoop.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 22时31分17秒
 =======================================================*/
#include "event_loop.h"
#include "epoll.h"
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
using namespace netlib;

EventLoop::EventLoop(int eventFd)
    :eventFd_(eventFd),epoll_(new Epoll(1024))
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
            else if(events_[i].events & EPOLLHUP)
            {
                //处理关闭事件
                closeCallback_();
            }
            else if(events_[i].events & EPOLLIN)
            {
                //处理读事件
                readCallback();   
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
}


