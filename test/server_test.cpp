/*======================================================
    > File Name: base_loop_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 17时23分27秒
 =======================================================*/
#include <sys/eventfd.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "server.h"
#include <functional>
#include <thread>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include "connection.h"
#include <memory>

int fd;
uint64_t buffer;

void fun(std::shared_ptr<netlib::Connection> p)
{
    printf("fd = %d\n",p->fd_);
}
int main(int argc,char **argv)
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;

    
    netlib::Server loop(argv[1],atoi(argv[2]),4);
    loop.setMessageCallback(fun);
    loop.start();       
    return 0;
}

