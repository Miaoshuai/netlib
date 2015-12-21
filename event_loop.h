/*======================================================
    > File Name: eventLoop.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 22时12分59秒
 =======================================================*/

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <memory>
#include <sys/epoll.h>
#include "epoll.h"
#include "callback.h"
#include "connection.h"
#include <stdio.h>
#include <map>

namespace netlib    //自定义命名空间netlib
{
    class EventLoop
    {
        public:
            EventLoop(int eventFd);
            ~EventLoop();
            void loop();
            void handleEventFdRead(void);
            void handleRead(int fd);
            void handleClose(int fd);
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
        private:
            typedef std::map<int,std::shared_ptr<Connection>> ConnectionMap;

            int eventFd_;  //用于主loop向其他loop传递新连接的文件描述符
            std::shared_ptr<Epoll> epoll_;  //所拥有的epoll循环
            struct epoll_event events_[1024];  //获取epoll的就绪事件
            messageCallback messageCallback_;    //消息回调
            closeCallback closeCallback_;  //关闭回调
            writeCompleteCallback writeCompleteCallback_;
            ConnectionMap connectionMap;
    };
}
#endif
