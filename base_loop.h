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

namespace netlib
{
    class BaseLoop
    {
        public:
        private:
            connectionCallback connectionCallback_;     //新连接的回调函数
    };
}

#endif

