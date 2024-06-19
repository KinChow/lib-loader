/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:22:13 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:22:56
 */

#ifdef _WIN32
#ifndef __WINDOWS_LIBLOADER_H__
#define __WINDOWS_LIBLOADER_H__

#include <Windows.h>
#include "ILibLoader.h"

class WindowsLibLoader final : public ILibLoader {
public:
    static WindowsLibLoader *Create();
    static void Destroy(WindowsLibLoader *loader);
    virtual ~WindowsLibLoader() override final;
    int OpenLib(const char *libName) override final;
    int CloseLib() override final;
    void *LoadFunc(const char *funcName) override final;

private:
    HINSTANCE m_handle{nullptr};
};

#endif  // __WINDOWS_LIBLOADER_H__
#endif  // _WIN32