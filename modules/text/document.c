/**
 * @file document.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include "document.h"
#include "utils_log.h"
#include "schedule.h"
#include "text.h"

typedef struct {
    uint32_t log_count;
} document_obj_args_t;

typedef struct {
    task_entry_t func;
    document_obj_args_t args;
} document_obj_t;

document_obj_t g_document_obj;

int document_proc_log(void *args)
{
// #define _PRE_DOCUMENT_DEMO
#ifdef _PRE_DOCUMENT_DEMO
    document_obj_args_t *obj_args = (document_obj_args_t *)args;
    obj_args->log_count++;
    log_print(0,0," document proc [%u] logs", obj_args->log_count);
#else
    text_ops(0);
#endif

    return 0;
}

int document_task_init(void)
{
    // schedule_task_init(g_document_obj.func, (void *)(&g_document_obj.args));
    return 0;
}

int document_init(void)
{
    log_print(0, 0, "enter!");
    memset(&g_document_obj, 0, sizeof(document_obj_t));
    g_document_obj.func = document_proc_log;
    g_document_obj.args.log_count = 20;

    text_init();
    return document_task_init();
}

int document_exit(void)
{
    log_print(0, 0, "enter!");
    text_deinit();
    return 0;
}
