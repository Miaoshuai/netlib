/*======================================================
    > File Name: server.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月20日 星期日 15时27分50秒
 =======================================================*/
#include "server.h"
#include <string>

using namespace netlib;

Server::Server(std::string ip,int port,int loopNumber)
    :baseLoopPtr_(new BaseLoop(ip,port,loopNumber))
{

}


Server::~Server()
{

}

void Server::start()
{
    baseLoopPtr_->start();
}


