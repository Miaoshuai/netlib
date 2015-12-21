/*======================================================
    > File Name: event_loop_thread_pool.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 11时25分59秒
 =======================================================*/
#ifndef EVENT_LOOP_THREAD_POOL_H_
#define EVENT_LOOP_THREAD_POOL_H_

#include <map>
#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include "callback.h"

namespace netlib
{
    class LoopThreadPool
    {
        public:
            LoopThreadPool(int number);
            ~LoopThreadPool();
            int getNextLoop();             //返回下一个loop的eventfd
            void start();                   //开始运行loop线程池
            int createEventFd();            //创建eventfd
            static void threadFunc(int eventFd,LoopThreadPool *loopThreadPool);              //线程函数，用于创建event_loop
            static void fun(void);                 //暂时用于测试的处理读回调的函数
            void setMessageCallback(messageCallback cb)
            {
                messageCallback_ = cb;
            }
            void setCloseCallback(closeCallback cb)
            {
                closeCallback_ = cb;
            }
            void setWriteCompleteCallback(writeCompleteCallback cb)
            {
                writeCompleteCallback_ = cb;
            } 
            messageCallback getMessageCallback(void)
            {
                return messageCallback_;   
            }
            closeCallback getCloseCallback(void)
            {
                return closeCallback_;
            }
            writeCompleteCallback getWriteCompleteCallback(void)
            {
                return writeCompleteCallback_;
            }
        private:
            int loopNumber_;    //loop_thread的总数
            int next_;          //下一个要执行任务的loop
            std::map<int,int> fdMap_; //用于保存整数与每个loop的eventfd的映射
            std::vector<std::shared_ptr<std::thread>> threadVector_; //保存新创建线程的对象的智能指针
            messageCallback messageCallback_;         //读回调
            closeCallback closeCallback_;       //关闭回调
            writeCompleteCallback writeCompleteCallback_;
    };   
}

#endif
