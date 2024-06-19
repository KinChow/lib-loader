/*
 * @Author: Zhou Zijian 
 * @Date: 2023-04-06 00:14:54 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-06-20 03:02:31
 */

#ifndef __ILIBLOADER_H__
#define __ILIBLOADER_H__

class ILibLoader {
public:
    /**
     * @brief Create a lib loader instance
     *
     * @return ILibLoader*
     */
    static ILibLoader *Create();

    /**
     * @brief Destroy a lib loader instance
     *
     * @param loader
     */
    static void Destroy(ILibLoader *loader);

    /**
     * @brief Destroy the ILibLoader object
     *
     */
    virtual ~ILibLoader() = default;

    /**
     * @brief Open a library
     *
     * @param libName library name
     * @return int return 0 if success, -1 if failed
     */
    virtual int OpenLib(const char *libName) = 0;

    /**
     * @brief Close the library
     *
     * @return int return 0 if success, -1 if failed
     */
    virtual int CloseLib() = 0;

    /**
     * @brief Load a function from the library
     *
     * @param funcName function name
     * @return void* return the function pointer if success, nullptr if failed
     */
    virtual void *LoadFunc(const char *funcName) = 0;
#if 0
protected:
    /**
     * @brief Construct a new lib loader instance
     *
     */
    ILibLoader() = default;

    /**
     * @brief delete copy constructor
     *
     */
    ILibLoader(const ILibLoader &) = delete;

    /**
     * @brief delete copy assignment operator
     * 
     * @return ILibLoader& 
     */
    ILibLoader &operator=(const ILibLoader &) = delete;

    /**
     * @brief delete move constructor
     *
     */
    ILibLoader(ILibLoader &&) = delete;

    /**
     * @brief delete move assignment operator
     * 
     * @return ILibLoader& 
     */
    ILibLoader &operator=(ILibLoader &&) = delete;
#endif
};

#endif  // __ILIBLOADER_H__