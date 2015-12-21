/*======================================================
    > File Name: buffer_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月21日 星期一 14时07分31秒
 =======================================================*/

#include "buffer.h"
#include <string>
#include <stdio.h>

int main(void)
{
    std::string s1("hello,world");
    std::string s2(2000,'a');
    std::string s3(1000,'b');

    netlib::Buffer buffer;
    buffer.append(s1);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s2);

    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s3);

    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    return 0;
}
