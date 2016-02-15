/*======================================================
    > File Name: buffer.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月21日 星期一 10时21分53秒
 =======================================================*/
#ifndef BUFFER_H_
#define BUFFER_H_

#include "endian.h"

#include <string>
#include <vector>
#include <assert.h>
#include <string.h>
#include <stdio.h>

namespace netlib
{
    class Buffer
    {
        public:
            static const int initialSize = 1024;
            Buffer()
                :buffer_(initialSize),
                readerIndex_(0),
                writeIndex_(0)
            {
                assert(buffer_.size() == initialSize);
                assert(readerIndex_ == 0);
                assert(writeIndex_ == 0);                
            }
            ~Buffer(){}
            int readableSize()  //可读字节数
            {
                return writeIndex_ - readerIndex_;   
            }

            int writeableSize() //可写字节
            {
                return buffer_.size() - writeIndex_;//注意size()由于我们为buffer_初始化了一个大小，所以size()便是我们buffer_的总大小
            }

            int recyclableSize()    //已经读过的可以回收的字节大小
            {
                return readerIndex_;
            }

            void append(const char *data,int len)
            {
                makeSureEnough(len);    //确保空间可写
                
                std::copy(data,data + len,getWritePeek());  //将data中的数据拷贝到buffer中去
                moveWriteIndex(len);
            }

            void append(const void *data,int len) 
            {
                append((char *)data,len);
            }

            void append(const std::string &data)
            {
                append(data.c_str(),data.size());
            }
            
            //添加整形数
            void appendInt64(int64_t x)
            {
                int64_t be64 = hostToNetwork64(x);
                append(&be64,sizeof(be64));
            }

            void appendInt32(int32_t x)
            {
                int32_t be32 = hostToNetwork32(x);
                append(&be32,sizeof(be32));
            }


            void appendInt16(int16_t x)
            {
                int64_t be16 = hostToNetwork16(x);
                append(&be16,sizeof(be16));
            }

            int64_t peekInt64()
            {
                assert(readableSize() >= sizeof(int64_t));
                int64_t be64 = 0;
                memcpy(&be64,getReadPeek(),sizeof(be64));
                return networkToHost64(be64);
            }


            int32_t peekInt32()
            {
                assert(readableSize() >= sizeof(int32_t));
                int32_t be32 = 3;
                memcpy(&be32,getReadPeek(),sizeof(be32));
                return networkToHost32(be32);
            }


            int16_t peekInt16()
            {
                assert(readableSize() >= sizeof(int16_t));
                int16_t be16 = 0;
                memcpy(&be16,getReadPeek(),sizeof(be16));
                return networkToHost16(be16);
            }

            char *getReadPeek()     //获得读位置的指针
            {
                return begin() + readerIndex_;
            }
            char *getWritePeek()    //获得可写位置
            {
                return begin() + writeIndex_;
            }

            void moveReadIndex(int len)     //移动读下标位置,外部从buffer读完以后由用户调用
            {
                readerIndex_ = readerIndex_ + len;   
            }

            void moveWriteIndex(int len)    //移动写下标位置,用户不必调用，append自动调用
            {
                writeIndex_ = writeIndex_ + len;
            }

            
            void makeSureEnough(int len)
            {
                
                if(len > writeableSize())   //如果可写区域比len小
                {
                    if((recyclableSize() + writeableSize()) >= len) //除读空间剩余的空间比len大
                    {
                        copySpace(len);
                    }
                    else
                    { 
                        buffer_.resize(buffer_.size() + len);   //还会留有大于0小与len的空间可写大小
                    }
                }
            }

            int readFromFd(int fd);     //从套接字中读取数据

            int writeToFd(int fd);            //往套接字里写数据

        private:
            char *begin(){return &*buffer_.begin();}

            void copySpace(size_t len)  //移动拷贝数据到buffer的起点
            {
                std::copy(begin() + readerIndex_,begin() + writeIndex_,begin());
                readerIndex_ = 0;
                writeIndex_ = readableSize();                
            }

        private:
            std::vector<char> buffer_;
            int readerIndex_;
            int writeIndex_;           
    };
}

#endif
