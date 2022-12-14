/**
 * @file utils_list.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stddef.h>
#include "utils_comm.h"
#include "utils_list.h"
#include "utils_log.h"

void utils_list_init(utils_list_t *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

void utils_list_push_back(utils_list_t *list, list_item_t *item)
{
    if (list->count == 0) {
        list->head = item;
        list->tail = item;
        list->count++;
        return;
    }

    list->tail->next = item;
    list->tail = item;
    list->count++;
    return;
}

list_item_t *utils_list_pop_front(utils_list_t *list)
{
    list_item_t *item = list->head;
    if (list->count == 0) {
        return NULL;
    }else if (list->count == 1) {
        list->tail = NULL;
        list->head = NULL;
    } else {
        list->head = list->head->next;
    }

    item->next = NULL;
    list->count--;

    return item;
}

void utils_list_clear(utils_list_t *list)
{
    list_item_t *item;
    while (list->count > 0) {
        item = utils_list_pop_front(list);
        utils_free(item);
    }
}
// #ifdef TEST_MODE

void utils_list_travel(utils_list_t *list, list_item_op_cb_t func)
{
    // log_print(0,0,"list count[%u]", list->count);
    list_item_t *item = list->head;
    for (uint32_t i = 0; i < list->count; i++) {
        if (func) {
            func(item);
        }
        item = item->next;
    }
}
// #endif
