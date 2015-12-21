/*======================================================
    > File Name: callback.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 23时48分52秒
 =======================================================*/
#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <functional>
#include "connection.h"
#include <memory>
namespace netlib
{
    typedef std::function<void(void)> connectionCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> messageCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> closeCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> writeCompleteCallback;
}

#endif
