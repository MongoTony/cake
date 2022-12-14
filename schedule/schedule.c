/**
 * @file schedule.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils_comm.h"
#include "schedule.h"
#include "utils_log.h"

schedule_context_t g_schedule_context;

#define schedule_set_state(_state)     \
do {                                   \
    g_schedule_context.state = _state; \
} while(0)
#define schdule_get_state() (g_schedule_context.state)

#define schedule_set_pid(_pid)     \
do {                                   \
    g_schedule_context.pid = _pid; \
} while(0)
#define schedule_get_pid() (g_schedule_context.pid)

#define context     (&g_schedule_context)
#define task_list   (&g_schedule_context.task_list)
#define task_mutex  (&g_schedule_context.task_mutex)
#define task_idx    (g_schedule_context.task_idx)

int schedule_init(void)
{
    log_print(0, 0, "init!");
    memset(context, 0, sizeof(*context));

    pthread_mutex_init(task_mutex, NULL);

    schedule_set_state(SCHEDULE_STATE_INIT);

    pthread_mutex_lock(task_mutex);
    utils_list_init(task_list);
    pthread_mutex_unlock(task_mutex);
    return 0;
}

int schedule_task_proc()
{
    pthread_mutex_lock(task_mutex);
    task_t *task = (task_t *)task_list->head;
    while (task) {
        if (task->func) {
            log_print(0, 0, "task[0x%x] task_id[0x%x]!", task, task->task_id);
            task->func(task->args);
        }
        task = (task_t *)task->next;
    }
    pthread_mutex_unlock(task_mutex);
}

int schedule_work()
{
    while (true) {
        log_print(0, 0, "running[%u]!", schdule_get_state());
        schedule_task_proc();
        sleep(1);
    }
}

void *schedule_entry(void *args)
{
    pthread_detach(pthread_self());

    log_print(0, 0, "enter, state = [%u]!", schdule_get_state());
    //dead loop
    schedule_work();
    // log_print(0, 0, "enter, state = [%u]!", schdule_get_state());
    return NULL;
}

int schedule_start(void)
{
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, schedule_entry, NULL);
    if (ret == 0) {
        log_print(0, 0, "sched create thread succ!");
        schedule_set_pid(pid);
        schedule_set_state(SCHEDULE_STATE_WORK);
    } else {
        log_print(0, 0, "sched create thread fail!");
    }

    return 0;
}

/**
 * @brief 获取 task id
 * 
 * @return uint16_t ：task_id值，0 不使用
 */
uint16_t schedule_next_task_id()
{
    uint16_t curr_task_id;
    uint16_t id;
    pthread_mutex_lock(task_mutex);
    curr_task_id = task_idx;
    curr_task_id++;
    if (curr_task_id == 0) {
        curr_task_id++;   
    }
    task_idx = curr_task_id;
    pthread_mutex_unlock(task_mutex);
    return curr_task_id;
}

int schedule_task_init(task_entry_t func, void *args)
{
    task_t *task = (task_t *)utils_malloc(sizeof(task_t));
    if (task == NULL) {
        log_print(0, 0, "task malloc fail!");
        return -1;
    }

    memset(task, 0, sizeof(task_t));
    task->args = args;
    task->func = func;
    task->task_id = schedule_next_task_id();
    log_print(0, 0, "task[0x%x] task_id[0x%x]!", task, task->task_id);
    task->next = NULL;
    pthread_mutex_lock(task_mutex);
    utils_list_push_back(task_list, (list_item_t *)task);
    pthread_mutex_unlock(task_mutex);
}

int schedule_task_exit(task_t *task)
{
    if (task != NULL) {
        log_print(0, 0, "task[0x%x] task_id[0x%x]!", task, task->task_id);
        // sleep(2);
        utils_free(task);
    }
}

int schedule_exit(void)
{
    log_print(0, 0, "enter!");
    task_t *task;

    pthread_mutex_lock(task_mutex);

    while(task_list->count > 0) {
        task = (task_t *)utils_list_pop_front(task_list);
        // log_print(0, 0, "task[0x%x] task_id[0x%x]!", task, task->task_id);
        schedule_task_exit(task);
    }

    pthread_mutex_unlock(task_mutex);

    pthread_mutex_destroy(task_mutex);
    log_print(0, 0, "exit!");
    return 0;
}
