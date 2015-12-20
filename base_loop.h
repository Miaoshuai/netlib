/*======================================================
    > File Name: base_loop.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 11时16分01秒
 =======================================================*/
#ifndef BASE_LOOP_H_
#define BASE_LOOP_H_

#include <map>
#include "callback.h"
#include "event_loop_thread_pool.h"
#include <memory>
#include <string>

namespace netlib
{
    class BaseLoop
    {
        public:
            BaseLoop(std::string ip,int porti,int loopNumber);  //构造传参确定开多少个loop
            ~BaseLoop();
            int createListenFd(void);  //创建监听套接字
            void startListen(void);      //开始监听
            void connectionHandle();    //连接回调可以在此之中调用
        private:
            std::string ip_;        //监听ip
            int         port_;      //监听端口
            int         listenFd;   //监听套接字
            std::shared_ptr<LoopThreadPool> loopThreadPoolPtr_  //线程池对象指针          
    };
}

#endif

