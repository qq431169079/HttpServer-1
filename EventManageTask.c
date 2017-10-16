#include "EventManageTask.h"

EventManageTask* CreateEventManageTask(EventTree* eventTree)
{
    EventManageTask* manage = (EventManageTask*)malloc(sizeof(EventManageTask));
    if(manage == NULL)
    {
        printf("%s\n", __func__);
        exit(-1);
    }
    manage->arg = manage;
    manage->CallHandel = ManageEvent;
    manage->eventTree = eventTree;
    manage->isLive = 1;
    pthread_mutex_init(&manage->lockIsLive, NULL);
    return manage;
}
void* ManageEvent(void* arg)
{
    EventManageTask* manage = (EventManageTask*)arg;
    plinkTab events = manage->eventTree->AllEvent;

    while(1)
    {
        events = manage->eventTree->AllEvent;
        printf("扫描超时任务\n");
        ForeachDeal(events, (void*)manage->eventTree, DealHandel);
        sleep(1);
    }
    return NULL;
}

void* DealHandel(plinkTab linkTab, void* arg, void* otherArg)
{
    printf("fuck\n");
    EventTree* tree = (EventTree*)otherArg;
    EventNode* node = (EventNode*)arg;
    int now = time(NULL);

    if(now - node->time > 10){
        DeleteEvent(tree, node);
    }
    return NULL;
}