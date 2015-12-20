/*======================================================
    > File Name: epoll.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 19时20分56秒
 =======================================================*/
#include "epoll.h"

#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

using namespace netlib;

Epoll::Epoll(int epollSize):epollSize_(epollSize)
{
    maxEvents_ = 1024;
    epollFd_ = epoll_create(epollSize_);
}

Epoll::~Epoll()
{
    close(epollFd_);
}

void Epoll::setNonBlocking(int fd)
{
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
}

void Epoll::addFd(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN  ;
    
    epoll_ctl(epollFd_,EPOLL_CTL_ADD,fd,&event);
    setNonBlocking(fd);
}

void Epoll::modFd(int fd,int events)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = events;
    epoll_ctl(epollFd_,EPOLL_CTL_MOD,fd,&event);
}

void Epoll::delFd(int fd)
{
    epoll_ctl(epollFd_,EPOLL_CTL_DEL,fd,0);
    close(fd);
}

int Epoll::wait(struct epoll_event *events)
{
    int count = epoll_wait(epollFd_,events,maxEvents_,-1);   //无超时时间
    return count; 
}






