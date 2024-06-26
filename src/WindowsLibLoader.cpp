/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:26:30 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:43:09
 */

#ifdef _WIN32
#include "WindowsLibLoader.h"

ILibLoader *ILibLoader::Create()
{
    return WindowsLibLoader::Create();
}

void ILibLoader::Destroy(ILibLoader *loader)
{
    WindowsLibLoader::Destroy(static_cast<WindowsLibLoader *>(loader));
}

WindowsLibLoader *WindowsLibLoader::Create()
{
    return new WindowsLibLoader;
}

void WindowsLibLoader::Destroy(WindowsLibLoader *loader)
{
    if (loader != nullptr) {
        delete loader;
    }
}

WindowsLibLoader::~WindowsLibLoader()
{
    CloseLib();
}

int WindowsLibLoader::OpenLib(const char *libName)
{
    if (!libName) {
        return -1;
    }
    m_handle = LoadLibraryA(libName);
    return m_handle ? 0 : -1;
}

int WindowsLibLoader::CloseLib()
{
    if (m_handle != nullptr) {
        FreeLibrary(m_handle);
    }
    return 0;
}

void *WindowsLibLoader::LoadFunc(const char *funcName)
{
    if (!funcName) {
        return nullptr;
    }
    return reinterpret_cast<void *>(GetProcAddress(m_handle, funcName));
}

#endif
