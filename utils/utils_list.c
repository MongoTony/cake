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
#include "utils_list.h"

void utils_list_init(utils_list_t *list)
{
    list->head = list->tail = NULL;
    list-> count = 0;
}

void utils_list_push_back(utils_list_t *list, list_item_t *item)
{
    if (list->count == 0) {
        list->head = list->tail = item;
        list->count++;
        return;
    }

    list->tail->next = item;
    item->prev = list->tail;
    list->tail = item;
    list->count++;
    return;
}