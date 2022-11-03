/**
 * @file text.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include "text.h"
#include "utils_log.h"
#include "schedule.h"

typedef struct {
    uint32_t log_count;
} text_obj_args_t;

typedef struct {
    task_entry_t func;
    text_obj_args_t args;
} text_obj_t;

#define MAX_TEXT_OBJ_SIZE 5
text_obj_t g_text_obj[MAX_TEXT_OBJ_SIZE];

int text_proc_log(void *args)
{
    text_obj_args_t *obj_args = (text_obj_args_t *)args;
    obj_args->log_count++;
    log_print(0,0," text proc [%u] logs", obj_args->log_count);
    return 0;
}

int text_task_init(void)
{
    for (uint32_t i = 0; i < MAX_TEXT_OBJ_SIZE; i++) {
        schedule_task_init(g_text_obj[i].func, (void *)(&g_text_obj[i].args));
    }
    return 0;
}

int text_init(void)
{
    memset(&g_text_obj, 0, MAX_TEXT_OBJ_SIZE * sizeof(text_obj_t));
    for (uint32_t i = 0; i < MAX_TEXT_OBJ_SIZE; i++) { 
        g_text_obj[i].func = text_proc_log;
        g_text_obj[i].args.log_count = i * 20;
    }

    return text_task_init();
}