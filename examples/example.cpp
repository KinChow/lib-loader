/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:57:56 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:34:09
 */

#define CL_TARGET_OPENCL_VERSION 100

#include <iostream>
#include <CL/cl.h>
#include "LibLoader.h"

using clGetPlatformIDsPtrFunc = decltype(&clGetPlatformIDs);

int main()
{
    void *handle = nullptr;
#ifdef _WIN32
    int ret = OpenLib("C:\\Windows\\System32\\OpenCL.dll", &handle);
#else
    int ret = OpenLib("/usr/lib/x86_64-linux-gnu/libOpenCL.so", &handle);
#endif
    clGetPlatformIDsPtrFunc funPtr = reinterpret_cast<clGetPlatformIDsPtrFunc>(LoadFunc(handle, "clGetPlatformIDs"));
    cl_uint platformNum;
    int err = funPtr(0, nullptr, &platformNum);
    if (err != CL_SUCCESS) {
        std::cout << "run opencl failed! err=" << err << std::endl;
        return -1;
    }
    std::cout << "platformNum=" << platformNum << std::endl;
    CloseLib(handle);
    return 0;
}
