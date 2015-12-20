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

namespace netlib
{
    typedef std::function<void(void)> connectionCallback;
    typedef std::function<void(void)> readCallback;
    typedef std::function<void(void)> closeCallback;
    typedef std::function<void(void)> writeCompleteCallback;
}

#endif
