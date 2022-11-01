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
#include "schedule.h"
#include "utils_log.h"

schedule_context_t g_schedule_context;

int schedule_init(void)
{
    log_print(0, 0, "init!");
    memset(&g_schedule_context, 0, sizeof(g_schedule_context));
    g_schedule_context.state = SCHEDULE_STATE_INIT;
    return 0;
}

int schedule_exit(void)
{
    log_print(0, 0, "exit!");
    return 0;
}

void *schedule_entry(void *args)
{
    pthread_detach(pthread_self());
    while (true) {
        log_print(0, 0, "sched thread running[%u]!", g_schedule_context.state);
        sleep(2);
    }

    return NULL;
}

int schedule_run(void)
{
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, schedule_entry, NULL);
    if (ret == 0) {
        log_print(0, 0, "sched create thread succ!");
        g_schedule_context.pid = pid;
        g_schedule_context.state = SCHEDULE_STATE_WORK;
        
    } else {
        log_print(0, 0, "sched create thread fail!");
    }

    return 0;
}
