/*======================================================
    > File Name: server.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 15时07分50秒
 =======================================================*/
#ifndef SERVER_H_
#define SERVER_H_

#include "base_loop.h"
#include <memory>
#include <string>
#include "callback.h"

namespace netlib
{
    class Server
    {
        public:
            Server(std::string ip,int port,int loopNumber);
            ~Server();
            void start(void);   //开始运行server
            void setConnectionCallback(connectionCallback cb)
            {
                connectionCallback_ = cb;
            }
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
            std::shared_ptr<BaseLoop> baseLoopPtr_; //保存baseLoop的智能指针
            connectionCallback connectionCallback_; //连接回调
            messageCallback messageCallback_;       //消息回调
            closeCallback closeCallback_;           //关闭回调
            writeCompleteCallback writeCompleteCallback_;//写完成回调
    };
}

#endif
