/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-05 23:59:59 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-02-04 03:13:48
 */

#ifndef ILIBLOADER
#define ILIBLOADER


#ifdef __cplusplus
extern "C" {
#endif
// 打开动态链接库
int OpenLib(const char *libName, void **handle);

// 加载函数指针
void *LoadFunc(void *handle, const char *funcName);

// 关闭动态链接库
int CloseLib(void *handle);

#ifdef __cplusplus
}
#endif

#endif  // ILIBLOADER