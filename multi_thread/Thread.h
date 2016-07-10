#ifndef _THREAD_H_
#define _THREAD_H_

#include <iostream>
#include <pthread.h>

#if (defined _linux) || (defined _unix)
#include <unistd.h>
#endif

#if (defined _WIN32) || (defined _WIN64) 
#include <windows.h>
#endif

using namespace std;

namespace multi_thread {
/************************************************
 * \brief 多线程
 *************************************************/
class Thread {
public:
    Thread() : t_id(0), isRunning(false) {}
    ~Thread() {}

    /************************************************
     * \brief 启动线程
     *************************************************/
    void Start();

    /************************************************
     * \brief 终止线程
     *************************************************/
    void Stop();

    /************************************************
     * \brief 使线程暂停milliseconds毫秒
     *
     * \param milliseconds 暂停时长
     *************************************************/
    void Sleep(int milliseconds);

    /************************************************
     * \brief 获取线程运行状态
     *
     * \return 线程运行状态
     *************************************************/
    bool State() const { return isRunning; }

    /************************************************
     * \brief 获取当前线程ID
     *
     * \return 当前线程ID
     *************************************************/
    pthread_t GetThreadID() const { return t_id; }

    /************************************************
     * \brief 等待线程推出
     *************************************************/
    void Join();

    /************************************************
     * \brief 线程上锁
     *************************************************/
    void Lock(pthread_mutex_t mutex);

    /************************************************
     * \brief 线程解锁
     *************************************************/
    void Unlock(pthread_mutex_t mutex);
protected:
    virtual void run() = 0;
private:
    pthread_t t_id; //线程ID
    int threadStatus;
    bool isRunning; //线程是否在运行

    /************************************************
     * \brief 线程运行函数
     *
     * \param args 线程运行函数的参数
     *
     * \return 线程运行的实体
     *************************************************/
    friend void *thread_proxy_func(void *args);
};

}

#endif // _THREAD_H_
