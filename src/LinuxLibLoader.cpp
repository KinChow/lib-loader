/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:26:30 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:43:25
 */

#ifdef __linux__
#include "LinuxLibLoader.h"

ILibLoader *ILibLoader::Create()
{
    return LinuxLibLoader::Create();
}

void ILibLoader::Destroy(ILibLoader *loader)
{
    LinuxLibLoader::Destroy(static_cast<LinuxLibLoader *>(loader));
}

LinuxLibLoader *LinuxLibLoader::Create()
{
    return new LinuxLibLoader;
}

void LinuxLibLoader::Destroy(LinuxLibLoader *loader)
{
    if (loader != nullptr) {
        delete loader;
    }
}

LinuxLibLoader::~LinuxLibLoader()
{
    CloseLib();
}

int LinuxLibLoader::OpenLib(const char *libName)
{
    if (!libName) {
        return -1;
    }
    m_handle = dlopen(libName, RTLD_LAZY);
    return m_handle ? 0 : -1;
}

int LinuxLibLoader::CloseLib()
{
    if (m_handle != nullptr) {
        dlclose(m_handle);
    }
    return 0;
}

void *LinuxLibLoader::LoadFunc(const char *funcName)
{
    if (!funcName) {
        return nullptr;
    }
    return dlsym(m_handle, funcName);
}

#endif
