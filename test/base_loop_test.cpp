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
#include "base_loop.h"
#include <functional>
#include <thread>
#include <assert.h>
#include <stdlib.h>
#include <string>

int fd;
uint64_t buffer;
int main(int argc,char **argv)
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;

    
    netlib::BaseLoop loop(argv[1],atoi(argv[2]),4);
    loop.start();       
    return 0;
}

