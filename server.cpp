/*======================================================
    > File Name: server.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 21时53分51秒
 =======================================================*/
#include "server.h"
#include <memory>
#include <string>

using namespace netlib;

Server::Server(std::string ip,int port,int loopNumber)
    :baseLoopPtr_(std::make_shared<BaseLoop>(ip,port,loopNumber))
{
    
}

Server::~Server()
{

}

void Server::start()
{
    baseLoopPtr_->setConnectionCallback(connectionCallback_);//设置连接回调
    baseLoopPtr_->setMessageCallback(messageCallback_);   //设置读回调函数
    baseLoopPtr_->setCloseCallback(closeCallback_);  //设置关闭回调函数
    baseLoopPtr_->setWriteCompleteCallback(writeCompleteCallback_);
    baseLoopPtr_->start();                          //开始循环
}
