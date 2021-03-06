#include "cl_accept_task.h"
#include "cl_pthread_pool.h"
#include "cl_event.h"
#include <stdio.h>

typedef struct manage{
    cl_base_task        accept_task;
    cl_pthread_pool*    pool;
}manage;

void* showf(void* arg)
{
    // cl_base_task* cb = arg;
    // cl_http_event* ht = cb->self;
    // printf("%d\n", cb->need_destroy);
    // if(cb->need_destroy == NEEDDIE)
    // {
    //     cb->destroy(cb);
    // }
    // free(arg);
    return NULL;
}

void* show(void* arg)
{
    manage* m = (manage*)arg;
    // while(1)
    // {
    //     // m->pool
    //     printf("%d\n", m->pool->finish_task->sum);
    //     cl_base_task* task = cl_link_get_front(m->pool->finish_task);
    //     if(task)
    //     {
    //         // task->destroy(task);
    //         free(task);
    //     }
    //
    //     // cl_link_each(m->pool->finish_task, NULL, showf);
    //     usleep(100);
    // }

    return NULL;
}

int main(int argc, char* argv[])
{
    cl_pthread_pool* pool = cl_pthread_pool_create();
    manage* m = malloc(sizeof(manage));
    m->accept_task.self = m;
    m->pool = pool;
    m->accept_task.handler = show;
    cl_pthread_pool_add_task(pool, cl_base_task_get_base(m, manage, accept_task));
    cl_event* event = cl_event_create(100, 100, pool);
    cl_accept_task* accept =  cl_accpet_task_create("0.0.0.0", "7777", 10, pool, event);
    cl_pthread_pool_add_task(pool, cl_base_task_get_base(accept, cl_accept_task, accept_task));
    cl_event_wait_event(event);
    while(1);
    return 0;
}
