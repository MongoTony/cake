/**
 * @file pool.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pool.h"

void pool_init(res_pool_t *pool, uint32_t block, uint32_t block_size, void *mem)
{
    pool->block = block;
    pool->block_size = block_size;

    utils_list_init(&(pool->free_list));

    for (uint32_t i = 0; i < block; i++) {
        list_item_t *item = (list_item_t *)((uint8_t *)mem + (i * block_size));
        utils_list_push_back(&(pool->free_list), item);
    }
}

void* pool_alloc(res_pool_t *pool)
{
    return utils_list_pop_front(&(pool->free_list));
}

void pool_free(res_pool_t *pool, void *addr)
{
    // (void)memset(addr, 0, pool->block_size);
    utils_list_push_back(&pool->free_list, (list_item_t*)addr);
}

#if _PRE_CAKE_DFT
bool pool_is_empty(res_pool_t *pool)
{
    return pool->free_list.count == 0;
}

#endif
