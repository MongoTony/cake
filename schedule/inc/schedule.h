/**
 * @file schedule.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <pthread.h>
#include <stdint.h>
#include "utils_list.h"

typedef int (*task_entry_t)(void *);

typedef struct {
    list_item_t *next;

    uint16_t task_id;
    task_entry_t func;
    void *args;
} task_t;

typedef enum {
    SCHEDULE_STATE_INIT,
    SCHEDULE_STATE_WORK,
    SCHEDULE_STATE_HALT,

    SCHEDULE_STATE_BUTT
} shedule_state_t;

typedef struct {
    pthread_t pid;
    uint8_t state;


    pthread_mutex_t task_mutex;
    utils_list_t task_list;

    pthread_mutex_t task_idx_mutex;
    uint16_t task_idx;

} schedule_context_t;

int schedule_init(void);
int schedule_start(void);
int schedule_exit(void);

int schedule_task_init(task_entry_t func, void *args);

#endif