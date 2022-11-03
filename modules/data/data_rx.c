/**
 * @file data_rx.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "data_rx.h"
#include "utils_log.h"
#include "schedule.h"

uint32_t g_data_rx_stat = 0;
 
int data_recv_package(void *args)
{
    g_data_rx_stat++;    
    log_print(0,0," data rx [%u] packages", g_data_rx_stat);
    return 0;
}

int data_init(void)
{
    schedule_task_init(data_recv_package, NULL);
}