/*======================================================
    > File Name: message.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年02月15日 星期一 20时15分22秒
 =======================================================*/
/*各种消息处理函数*/

#pragma once

#include <memory>
#include "connection.h"
#include "message.pb.h"
#include "codec.h"
#include "mysql.h"
#include <list>
#include <string>

class User
{
    public:
        std::string userName;
        int fd;   
};

class MessageType
{
    public:
        typedef std::shared_ptr<Login> LoginPtr;
        typedef std::shared_ptr<Register> RegisterPtr;
        
        MessageType(ProtobufCodec codec)
            :codec_(codec)
        {}

        void onLogin(netlib::connectionPtr conn,LoginPtr message);

        void onRegister(netlib::connectionPtr conn,RegisterPtr message);
    private:
        Sql sql_;   //数据库
        std::list<std::shared_ptr<User>> userList_;       
        ProtobufCodec codec_;
};
