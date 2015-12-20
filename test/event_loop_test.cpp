/*======================================================
    > File Name: event_loop_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 15时48分50秒
 =======================================================*/
#include <sys/eventfd.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "event_loop.h"
#include <functional>
#include <thread>
#include <assert.h>

int fd;
uint64_t buffer;

void readCallback(void)
{
    printf("可读触发\n");
}

void threadFunc(void)
{
    uint64_t buf = 7;
    sleep(2);
    int ret = write(fd,&buf,sizeof(buf));
    assert(ret == sizeof(buf));
    printf("写完\n");
}

int main(void)
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;

    if((fd = eventfd(0,0)) == -1)   //创建事件驱动的文件描述符
    {
        printf("创建失败\n");
    }
    
    std::thread t(threadFunc);

    netlib::EventLoop loop(fd);
    loop.setReadCallback(readCallback);
    loop.loop();
        
    return 0;
}
