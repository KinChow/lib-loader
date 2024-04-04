/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-08 23:17:15 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2023-04-08 23:27:35
 */

#ifdef __linux__
#ifndef LINUX_LIBLOADER
#define LINUX_LIBLOADER

#include <dlfcn.h>
#include "LibLoader.h"

class LinuxLibLoader : public LibLoader {
public:
    int OpenLib(const char *libName) override;
    int CloseLib() override;
    void *LoadFunc(const char *funcName) override;

private:
    void *m_handle{nullptr};
};

#endif  // LINUX_LIBLOADER
#endif  // __linux__
