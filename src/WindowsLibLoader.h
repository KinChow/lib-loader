/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:22:13 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2023-04-08 23:23:07
 */

#ifdef _WIN32
#ifndef WINDOWS_LIBLOADER
#define WINDOWS_LIBLOADER

#include <Windows.h>
#include "LibLoader.h"

class WindowsLibLoader : public LibLoader {
public:
    int OpenLib(const char *libName) override;
    int CloseLib() override;
    void *LoadFunc(const char *funcName) override;

private:
    HINSTANCE m_handle{nullptr};
};

#endif  // WINDOWS_LIBLOADER
#endif  // _WIN32