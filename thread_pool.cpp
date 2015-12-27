/*======================================================
    > File Name: thread_pool.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月27日 星期日 13时53分34秒
 =======================================================*/
#include "thread_pool.h"
#include <stdio.h>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <unistd.h>

using namespace netlib;

ThreadPool::ThreadPool(int threadNumber)
    :threadNumber_(threadNumber),
    running_(true),
    threads_(threadNumber_)
{
    
}

ThreadPool::~ThreadPool()
{
    if(running_)
    {
        stop();
    }
}

bool ThreadPool::start(void)
{
    for(int i = 0; i < threadNumber_; i++)
    {
        threads_.push_back(std::make_shared<std::thread>(std::bind(&ThreadPool::threadWork,this)));//循环创建线程       
    }
    usleep(500);
    printf("线程池开始运行\n");
    return true;   
}

bool ThreadPool::stop(void)
{
    if(running_)
    {
        running_= false;
        for(auto t : threads_)
        {
            t->join();  //循环等待线程终止
        }
    }
    return true;
}

bool ThreadPool::append(Task task)
{
    std::lock_guard<std::mutex> guard(mutex_);
    tasks_.push_front(task);   //将该任务加入任务队列
    condition_empty_.notify_one();//唤醒某个线程来执行此任务
    return true;
}

void ThreadPool::threadWork(void)
{
    Task task = NULL;
    while(running_)
    {   
        {
            std::lock_guard<std::mutex> guard(mutex_);
            if(tasks_.empty())
            {
                condition_empty_.wait(mutex_);  //等待有任务到来被唤醒
            }
            if(!tasks_.empty())
            {
                task = tasks_.front();  //从任务队列中获取最开始任务
                tasks_.pop_front();     //将取走的任务弹出任务队列
            }
            else
            {
                continue;
            }
        }
        task(); //执行任务
    }
}


