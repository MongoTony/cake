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

typedef enum {
    SCHEDULE_STATE_INIT,
    SCHEDULE_STATE_WORK,
    SCHEDULE_STATE_HALT,

    SCHEDULE_STATE_BUTT
} shedule_state_t;

typedef struct {
    /* data */
    pthread_t pid;
    uint8_t state;


} schedule_context_t;

int schedule_init(void);
int schedule_run(void);
int schedule_exit(void);
#endif