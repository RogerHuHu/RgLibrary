#include "Thread.hpp"

namespace multi_thread {
/*
 * 线程运行函数
 */
void *thread_proxy_func(void *args) {
    Thread *thread = static_cast<Thread *>(args);
    thread->run();
    return NULL;
}

/*
 * 启动线程
 */
void Thread::Start() {
    if(pthread_create(&t_id, NULL, thread_proxy_func, this) == 0) {
        isRunning = true;
        pthread_mutex_init(&multiThreadMutex, NULL);
    }
}

/*
 * 终止线程
 */
void Thread::Stop() {
    if(isRunning) {
        pthread_cancel(t_id);
        t_id = 0;
        isRunning = false;
        pthread_mutex_destroy(&multiThreadMutex);
    }
}

/*
 * 使线程暂停milliseconds毫秒
 */
void Thread::Sleep(int milliseconds) {
#ifdef linux
    int s = milliseconds / 1000;
    int us = (milliseconds % 1000) * 1000;

    if(s > 0) sleep(s);
    if(us > 0) usleep(us);
#endif

#ifdef WIN32  //call system api
    ::Sleep(milliseconds);
#endif
}

/*
 * 等待线程结束
 */
void Thread::Join() {
    if(t_id > 0) pthread_join(t_id, NULL);
    t_id = 0;
    isRunning = false;
}

/*
 * 线程锁
 */
void Thread::Lock() {
    pthread_mutex_lock(&multiThreadMutex);
}

/*
 * 线程解锁
 */
void Thread::Unlock() {
    pthread_mutex_unlock(&multiThreadMutex);
}

}
