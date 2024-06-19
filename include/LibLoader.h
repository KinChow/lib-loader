/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-05 23:59:59 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 02:03:41
 */

#ifndef __LIBLOADER_H__
#define __LIBLOADER_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Open a dynamic link library
 * 
 * @param libName library name
 * @param handle handle of the library
 * @return int return 0 if success, -1 if failed
 * @note The caller is responsible for closing the library
 */
int OpenLib(const char *libName, void **handle);

/**
 * @brief Load a function from the library
 * 
 * @param handle handle of the library
 * @param funcName function name
 * @return void* return the function pointer if success, nullptr if failed
 */
void *LoadFunc(void *handle, const char *funcName);

/**
 * @brief Close the library
 * 
 * @param handle handle of the library
 * @return int return 0 if success, -1 if failed
 */
int CloseLib(void *handle);

#ifdef __cplusplus
}
#endif

#endif  // __LIBLOADER_H__