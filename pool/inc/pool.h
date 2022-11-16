/**
 * @file pool.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef POOL_H
#define POOL_H


#include <stdbool.h>
#include <stdint.h>

#include "utils_list.h"

typedef struct {
    uint32_t block;
    uint32_t block_size;
    
    utils_list_t free_list;
} res_pool_t;

void pool_init(res_pool_t *pool, uint32_t block, uint32_t block_size, void *mem);
void* pool_alloc(res_pool_t *pool);
void pool_free(res_pool_t *pool, void *addr);
#endif