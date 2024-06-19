/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:11:43 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 03:04:17
 */


#include "LibLoader.h"
#include "ILibLoader.h"

int OpenLib(const char *libName, void **handle)
{
    *handle = nullptr;
    ILibLoader *libLoader = ILibLoader::Create();
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
    auto libLoader = static_cast<ILibLoader *>(handle);
    return libLoader->LoadFunc(funcName);
}

int CloseLib(void *handle)
{
    if (handle == nullptr) {
        return -1;
    }
    auto libLoader = static_cast<ILibLoader *>(handle);
    int ret = libLoader->CloseLib();
    ILibLoader::Destroy(libLoader);
    return ret;
}