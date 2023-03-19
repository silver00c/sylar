## 线程库
[线程的三种实现](https://zhuanlan.zhihu.com/p/165991129)
```
Thread类

```
pthread pthread_create

C11的互斥量没有读写分离的方式

互斥量 mutex
信号量 semaphore

```
//semaphore
#include <semaphore>
int sem_init(sem_t* sem, int pshared, unsigned int value)
int sem_destory(sem_t* sem)
int sem_wait(sem_t sem)
int sem_trywait(sem_t* sem)
int sem_post(sem_t* sem)
wait()
notify()
sem_t m_semphore;
```


```
//mutex
#include <pthread>
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t * mutexattr);
int pthread_mutex_destory(pthread_mutex_t* mutex);
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```