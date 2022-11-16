/**
 * @file doc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include "doc.h"
#include "utils_log.h"
#include "schedule.h"
#include "text.h"

typedef struct {
    uint32_t log_count;
} doc_obj_args_t;

typedef struct {
    task_entry_t func;
    doc_obj_args_t args;
} doc_obj_t;

doc_obj_t g_doc_obj;

int doc_proc_log(void *args)
{
#define _PRE_DOC_DEMO
#ifdef _PRE_DOC_DEMO
    doc_obj_args_t *obj_args = (doc_obj_args_t *)args;
    obj_args->log_count++;
    log_print(0,0," document proc [%u] logs", obj_args->log_count);
#else
    text_show();
#endif

    return 0;
}

int doc_task_init(void)
{
    schedule_task_init(g_doc_obj.func, (void *)(&g_doc_obj.args));
    return 0;
}

int doc_init(void)
{
    log_print(0, 0, "enter!");
    memset(&g_doc_obj, 0, sizeof(doc_obj_t));
    g_doc_obj.func = doc_proc_log;
    g_doc_obj.args.log_count = 20;

    text_init();
    return doc_task_init();
}

int doc_exit(void)
{
    log_print(0, 0, "enter!");
    text_deinit();
    return 0;
}
