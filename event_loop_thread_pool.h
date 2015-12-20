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

namespace netlib
{
    class LoopThreadPool
    {
        public:
            typedef std::function<void(void)> threadFunc;
            LoopThreadPool();
            ~LoopThreadPool();
            void setLoopNumber(int number); //用于设置loop的数量
            int getNextLoop();             //返回下一个loop的eventfd
            void start();                   //开始运行loop线程池
            int createEventFd();            //创建eventfd
            void threadFunc();              //线程函数，用于创建event_loop
            void fun(void);                 //暂时用于测试的处理读回调的函数
        private:
            int loopNumber_;    //loop_thread的总数
            int next_;          //下一个要执行任务的loop
            std::map<int,int> fdMap_; //用于保存整数与每个loop的eventfd的映射
            std::vector<std::shared_ptr<thread>> threadVector_; //保存新创建线程的对象的智能指针

    };   
}

#endif
