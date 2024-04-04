/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:11:43 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2023-04-08 23:29:59
 */

#ifdef _WIN32
#include "WindowsLibLoader.h"
#else
#include "LinuxLibLoader.h"
#endif
#include "ILibLoader.h"

int OpenLib(const char *libName, void **handle)
{
    *handle = nullptr;
#ifdef _WIN32
    LibLoader *libLoader = new WindowsLibLoader;
#else
    LibLoader *libLoader = new LinuxLibLoader;
#endif
    if (libLoader == nullptr) {
        return -1;
    }
    *handle = static_cast<void *>(libLoader);
    return libLoader->OpenLib(libName);
}

void *LoadFunc(void *handle, const char *funcName)
{
    if (handle == nullptr) {
        return nullptr;
    }
    auto libLoader = static_cast<LibLoader *>(handle);
    return libLoader->LoadFunc(funcName);
}

int CloseLib(void *handle)
{
    if (handle == nullptr) {
        return -1;
    }
    auto libLoader = static_cast<LibLoader *>(handle);
    handle = nullptr;
    return libLoader->CloseLib();
}