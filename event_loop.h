/*======================================================
    > File Name: eventLoop.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 22时12分59秒
 =======================================================*/

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <memory.h>
#include <sys/epoll.h>
#include "epoll.h"
#include "callback.h"

namespace netlib    //自定义命名空间netlib
{
    class EventLoop
    {
        public:
            EventLoop();
            ~EventLoop();
            void loop();
            void handleEventFdRead(void);
            void setReadCallback(readCallback &cb)
            {
                readCallback_ = cb;
            }
            void setCloseCallback(closeCallback &cb)
            {
                closeCallback_ = cb;
            }

        private:
         eventFd_;  //用于主loop向其他loop传递新连接的文件描述符
         shared_ptr<Epoll>;  //所拥有的epoll循环
         struct event* events_;  //获取epoll的就绪事件
         readCallback readCallback_;    //读回调
         closeCallback closeCallback_;  //关闭回调
    };
}
#endif
