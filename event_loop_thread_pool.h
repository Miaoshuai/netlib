/*======================================================
    > File Name: event_loop_thread_pool.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 11时25分59秒
 =======================================================*/
#ifndef EVENT_LOOP_THREAD_POOL_H_
#define EVENT_LOOP_THREAD_POOL_H_

#include <thread>
#include <map>
#include <sys/eventfd.h>

namespace netlib
{
    class LoopThreadPool
    {
        public:
            LoopThreadPool();
            ~LoopThreadPool();
            void setLoopNumber(int number); //用于设置loop的数量
            void getNextLoop();             //用于下个loop让其执行添加新连接任务
            void start();                   //开始运行loop线程池
        private:
            int loopNumber_;    //loop_thread的总数
            int next_;          //下一个要执行任务的loop
            std::map<int,int> loopFd //用于保存整数与每个loop的eventfd的映射
    };   
}

#endif
