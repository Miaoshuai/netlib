/*======================================================
    > File Name: buffer.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月21日 星期一 12时34分45秒
 =======================================================*/

#include "buffer.h"
#include <sys/uio.h>    //readv
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
using namespace netlib;

int Buffer::readFromFd(int fd)    //作为inputBuffer从套接字中读取数据到buffer中
{
    if(writeableSize() > 1024*10)   //如果可用空间大于10240则不必为其开辟栈空间
    {
        int count = read(fd,getWritePeek(),writeableSize());
        assert(count >= 0);

        writeIndex_ += count;
        return count;
    }
    else
    {
        char extrabuf[65536];
        struct iovec vec[2];

        int writeable = writeableSize();
        vec[0].iov_base = getWritePeek();
        vec[0].iov_len = writeableSize();
        vec[0].iov_base = extrabuf;
        vec[0].iov_len = sizeof(extrabuf);

        int count = readv(fd,vec,2);    //readv读取数据,注意readv用完一块才会用下一块
        assert(count >= 0);
        if(count <= writeableSize())    //去读到的数据buffer可以容纳
        {
            writeIndex_ += count;
        }
        else
        {
            //buffer不够用，有部分数据在栈中，在将其添加到buffer中
            writeIndex_ = buffer_.size();   //注意我们readv的时候没用append所以得手动增加writeIndex_
            append(extrabuf,count - writeable);
        }
        return count;
    }
    return 0;  
}

int Buffer::writeToFd(int fd)     //作为outputBuffer将buffer中的数据写入到套接字中
{
    int count = write(fd,getReadPeek(),readableSize()); //将buffer中的数据写入fd中
    assert(count >= 0);

    moveReadIndex(count);   //移动读下标
    return count;
}
