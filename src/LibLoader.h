/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:14:54 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2023-04-06 01:41:38
 */

#ifndef LIBLOADER
#define LIBLOADER

#include <string>

class LibLoader {
public:
    virtual int OpenLib(const char *libName)
    {
        return 0;
    }
    virtual int CloseLib()
    {
        return 0;
    }
    virtual void *LoadFunc(const char *funcName)
    {
        return nullptr;
    }
};

#endif  // LIBLOADER