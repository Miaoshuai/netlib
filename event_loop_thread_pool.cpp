/*======================================================
    > File Name: event_loop_thread_pool.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 11时42分11秒
 =======================================================*/

#include "event_loop_thread_pool.h"
#include "event_loop.h"
#include <assert.h>
#include <sys/eventfd.h>
#include <thread>
#include <map>
#include <memory>

using namespace netlib;

LoopThreadPool::LoopThreadPool()
{
    loopNumber_ = 0;
    next_ = 1;
}


LoopThreadPool::~LoopThreadPool()
{

}

void LoopThreadPool::setLoopNumber(int number)
{
    loopNumber_ = number;
}


int LoopThreadPool::getNextLoop()
{
    int fd = fdMap_[next_];
    if(next_ == loopNumber_)
    {
        next_ = 1;   //再次回到第一个循环
    }
    else
    {
        next_++;
    }
    return fd;
}


void LoopThreadPool::start()
{
    int fd;
    for(int i = 1; i <= loopNumber_; i++)
    {
        fd = createEventFd();
        fdMap_.pushback(std::pair<int,int>(i,fd));   //将编号及对应的fd存入map
        threadVector_.push_back(make_shared<thread>(threadFunc,fd));    //将新创建的线程对象加入容器中
    }
          
}

int LoopThreadPool::createEventFd()
{
    int fd = eventfd(0,EFD_NONBLOCK);
    assert(fd > 0);
    return fd;
}

void threadFunc(int eventFd)
{
    EventLoop loop(eventFd);
    loop.setReadCallback(fun);  //设置读回调
    loop.loop();                //启动循环
}

void fun(void)
{
    printf("读事件发生\n");
}
