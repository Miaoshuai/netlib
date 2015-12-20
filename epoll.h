/*======================================================
    > File Name: epoll.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 19时20分06秒
 =======================================================*/
#ifndef EPOLL_H_
#define EPOLL_H_

#include <sys/epoll.h>
namespace netlib
{
    class Epoll
    {
        public:
            Epoll(int epollSize);
            ~Epoll();
            void setNonBlocking(int fd);     //将套接字描述符设为非阻塞
            void addFd(int fd);         //向epoll内核事件表添加事件
            void modFd(int fd,int events);         //将内核中某个套接字所对应的事件修改
            void delFd(int fd);         //将epoll事件表中的某个事件删除
            int wait(struct epoll_event *events);
        private:
            int epollSize_;     //epoll内核事件表的大小
            int epollFd_;       //epoll内核事件表的描述符
            int maxEvents_;         //epoll_wait最多监听的事件个数
    };
}
#endif
