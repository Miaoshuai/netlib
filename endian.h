/*======================================================
    > File Name: endian.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年01月30日 星期六 00时00分42秒
 =======================================================*/
#pragma once

#include <stdint.h>
#include <endian.h>

namespace netlib
{
    uint64_t hostToNetwork64(uint64_t host64)
    {
        return htobe64(host64);
    }

    uint32_t hostToNetwork32(uint32_t host32)
    {
        return htobe32(host32);
    }

    uint16_t hostToNetwork16(uint16_t host16)
    {
        return htobe16(host16);
    }

    uint64_t networkToHost64(uint64_t net64)
    {
        return be64toh(net64);
    }

    uint32_t networkToHost32(uint32_t net32)
    {
        return be32toh(net32);
    }

    uint16_t networkToHost16(uint16_t net16)
    {
        return be16toh(net16);
    }
}
