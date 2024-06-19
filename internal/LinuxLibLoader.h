/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-08 23:17:15 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:25:46
 */

#ifdef __linux__
#ifndef __LINUX_LIBLOADER_H__
#define __LINUX_LIBLOADER_H__

#include <dlfcn.h>
#include "ILibLoader.h"

class LinuxLibLoader final : public ILibLoader {
public:
    static LinuxLibLoader *Create();
    static void Destroy(LinuxLibLoader *loader);
    virtual ~LinuxLibLoader() override final;
    int OpenLib(const char *libName) override final;
    int CloseLib() override final;
    void *LoadFunc(const char *funcName) override final;

private:
    void *m_handle{nullptr};
};

#endif  // __LINUX_LIBLOADER_H__
#endif  // __linux__
