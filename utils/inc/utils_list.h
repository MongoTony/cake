/**
 * @file utils_list.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTILS_LIST_H
#define UTILS_LIST_H

#include <stdint.h>

typedef struct list_item{
    struct list_item *next;
} list_item_t;

typedef struct {
    list_item_t *head;
    list_item_t *tail;

    uint32_t count;
} utils_list_t;

void utils_list_init(utils_list_t *list);

void utils_list_push_back(utils_list_t *list, list_item_t *item);
list_item_t *utils_list_pop_front(utils_list_t *list);

void utils_list_clear(utils_list_t *list);

// #ifdef TEST_MODE
typedef void *(list_item_op_cb_t)(void *);
void utils_list_travel(utils_list_t *list, list_item_op_cb_t func);

// #endif

#endif
