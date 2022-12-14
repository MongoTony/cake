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
#include "msg.h"
#include "schedule.h"
#include "utils_log.h"

#define MAX_MSG_SIZE 100
res_pool_t g_msg_pool;
msg_t g_msg_mem[MAX_MSG_SIZE];
utils_list_t g_msg_list;


void msg_pool_init()
{
    pool_init(&g_msg_pool, MAX_MSG_SIZE, sizeof(msg_t), (void *)g_msg_mem);
}

msg_t *msg_alloc()
{
    return (msg_t *)pool_alloc(&g_msg_pool);
}

void msg_free(msg_t *msg)
{
    pool_free(&g_msg_pool, msg);
}

void msg_send(msg_t *msg)
{
    utils_list_push_back(&g_msg_list, (list_item_t *)msg);
}

int msg_recv(void *args)
{
    msg_t *msg = (msg_t *)utils_list_pop_front(&g_msg_list);
    if (msg->src_mid >= MOD_ID_BUTT || msg->dst_mid >= MOD_ID_BUTT) {
        return 1;
    }
    /**
     * @brief TODO : MSG DISPATCH
     * 
     */

    return 0;
}

void msg_task_init(void)
{
    schedule_task_init(msg_recv, NULL);
}

int msg_init(void)
{
    log_print(0, 0, "enter!");
    msg_pool_init();
    msg_task_init();

    utils_list_init(&g_msg_list);

    return 0;
}

int msg_exit(void)
{
    log_print(0, 0, "enter!");
    return 0;
}

// #define _PRE_MSG_DEMO 1
// #ifdef _PRE_MSG_DEMO

uint32_t demo_send_msg(mod_id_t src_mid, mod_id_t dst_mid, msg_id_t msg_id, uint32_t len)
{
    msg_t *msg = msg_alloc();
    if (msg == NULL) {
        return 1;
    }
    msg->src_mid = src_mid;
    msg->dst_mid = dst_mid;
    msg->msg_id = msg_id;
    msg_send(msg);
    return 0;
}

void demo_app()
{    
}
// #endif
