#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

//编译时需要增加-lpthread
//gcc a.c -lpthread 
#define NTHREAD 6400

enum
{
    T_FREE = 0,
    T_LIVE,
    T_DEAD,
};

struct thread
{
    int id, status;
    pthread_t thread;
    void (*entry)(int);
};

struct thread tpool[NTHREAD], *tptr = tpool;

void *wrapper(void *arg)
{

    struct thread *thread = (struct thread *)arg;
    thread->entry(thread->id);
    return NULL;
}


//输入一个函数，就等于创建了一个线程号。
void create(void *fn)
{
    assert(tptr - tpool < NTHREAD);
    *tptr = (struct thread){
        .id = tptr - tpool + 1,
        .status = T_LIVE,
        .entry = fn,
    };
    pthread_create(&(tptr->thread), NULL, wrapper, tptr);//第一个参数为指向线程标识符的指针。
                                                        //第二个参数用来设置线程属性。
                                                        //第三个参数是线程运行函数的起始地址。
                                                        //最后一个参数是运行函数的参数。
    ++tptr;
}


//等待函数
void join()
{
    for (int i = 0; i < NTHREAD; i++)
    {
        struct thread *t = &tpool[i];
        if (t->status == T_LIVE)
        {
            pthread_join(t->thread, NULL);
            t->status = T_DEAD;
        }
    }
}

__attribute__((destructor)) void cleanup()
{
    join();
}