/**
 * @file document.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "pool.h"
#include "utils_comm.h"
#include "schedule.h"
#include "data.h"
#include "utils_log.h"

typedef struct {
    uint32_t curr_used_chan_num;
    uint32_t curr_free_chan_num;

    uint32_t malloc_chan_times;
    uint32_t free_chan_times;
} data_chan_stat_t;

data_chan_stat_t g_data_chan_stat;

#define data_chann_stat_inc(field) stat_inc(g_data_chan_stat.field)

res_pool_t g_data_chan_pool;
data_chan_t g_data_chan_mem[MAX_DATA_CHAN_SIZE];


void data_chan_pool_init()
{
    pool_init(&g_data_chan_pool, MAX_DATA_CHAN_SIZE, sizeof(data_chan_t), (void *)g_data_chan_mem);
}

data_chan_t *data_chan_alloc()
{
    data_chann_stat_inc(malloc_chan_times);
    return (data_chan_t *)pool_alloc(&g_data_chan_pool);
}

void data_chan_free(data_chan_t *data_chan)
{
    data_chann_stat_inc(free_chan_times);
    pool_free(&g_data_chan_pool, data_chan);
}

int data_chan_stat_show(void *arg)
{
    log_print(0, 0, "malloc_chan_times : %u!", g_data_chan_stat.malloc_chan_times);
    log_print(0, 0, "free_chan_times   : %u!", g_data_chan_stat.free_chan_times);
}

void data_task_init(void)
{
    schedule_task_init(data_chan_stat_show, NULL);
}

int data_init(void)
{
    log_print(0, 0, "enter!");

    data_chan_pool_init();

    data_task_init();
    return 0;
}

int data_exit(void)
{
    log_print(0, 0, "enter!");
    return 0;
}
