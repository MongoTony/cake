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

#include <stdint.h>

typedef struct list_item{
    struct list_item *next;
    struct list_item *prev;
} list_item_t;

typedef struct {
    list_item_t *head;
    list_item_t *tail;

    uint32_t count;
} utils_list_t;

void utils_list_init(utils_list_t *list);

void utils_list_push_back(utils_list_t *list, list_item_t *item);
