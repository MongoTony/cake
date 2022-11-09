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

#define MAX_DOC_OBJ_SIZE 2
doc_obj_t g_doc_obj[MAX_DOC_OBJ_SIZE];

int doc_proc_log(void *args)
{
    doc_obj_args_t *obj_args = (doc_obj_args_t *)args;
    obj_args->log_count++;
    log_print(0,0," document proc [%u] logs", obj_args->log_count);

    // text_show();
    return 0;
}

int doc_task_init(void)
{
    for (uint32_t i = 0; i < MAX_DOC_OBJ_SIZE; i++) {
        schedule_task_init(g_doc_obj[i].func, (void *)(&g_doc_obj[i].args));
    }
    return 0;
}

int doc_init(void)
{
    log_print(0, 0, "enter!");
    memset(&g_doc_obj, 0, MAX_DOC_OBJ_SIZE * sizeof(doc_obj_t));
    for (uint32_t i = 0; i < MAX_DOC_OBJ_SIZE; i++) { 
        g_doc_obj[i].func = doc_proc_log;
        g_doc_obj[i].args.log_count = i * 20;
    }

    text_init();
    return doc_task_init();
}

int doc_exit(void)
{
    log_print(0, 0, "enter!");
    text_deinit();
    return 0;
}
