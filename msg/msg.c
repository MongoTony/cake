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

#include "utils_comm.h"
#include "pool.h"
#include "msg.h"
#include "schedule.h"
#include "utils_log.h"

#define MAX_MSG_SIZE 100
res_pool_t g_msg_pool;
msg_t g_msg_mem[MAX_MSG_SIZE];
utils_list_t g_msg_list;

msg_tab_item_t *g_msg_tab[MOD_ID_BUTT];

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
    if (msg == NULL) {
        return;
    }

    pool_free(&g_msg_pool, msg);
}

msg_op_t *msg_find_op(msg_tab_item_t *tab, msg_id_t msg_id)
{
    while (tab->op != NULL) {
        if (tab->msg_id == msg_id) {
            return tab->op;
        }
        tab++;    
    }

    return NULL;
}

uint32_t msg_proc(msg_t *msg)
{
    if (msg == NULL) {
        return RET_CODE_PTR_NULL;
    }
    msg_head_t *head = &(msg->payload);
    if (head->src_mid >= MOD_ID_BUTT || head->dst_mid >= MOD_ID_BUTT) {
        log_print(0, 0, "src_mod [%u] dst_mod[%u] MOD_ID_BUTT[%u]!", head->src_mid, head->dst_mid, MOD_ID_BUTT);
        return RET_CODE_MSG_MOD_OVER;
    }

    if (head->msg_id > MSG_ID_BUTT) {
        return RET_CODE_MSG_ID_OVER;
    }

    msg_op_t *op = msg_find_op(g_msg_tab[head->dst_mid], head->msg_id);
    if (op == NULL) {
        log_print(0, 0, "Tab[%p] has no op for the msg_id[0x%x]", g_msg_tab[head->dst_mid], head->msg_id);
        return RET_CODE_PTR_NULL;
    }
    
    log_print(0, 0, "src_mod[%u] dst_mod[%u] msg_id[0x%x] !", head->src_mid, head->dst_mid, head->msg_id);
    return op(msg);
}

int msg_dispatch(void *args)
{
    while (g_msg_list.count > 0) {
        msg_t *msg = (msg_t *)utils_list_pop_front(&g_msg_list);
        ret_code_t ret = msg_proc(msg);
        if (ret != RET_CODE_SUCCESS) {
            log_print(0, 0, "msg proc ret[%u] is fail!", ret);
        }

        msg_free(msg);
    }

    return RET_CODE_SUCCESS;
}

void msg_task_init(void)
{
    schedule_task_init(msg_dispatch, NULL);
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

void msg_send(msg_t *msg)
{
#ifdef PRE_FEATURE_MSG_DISPATCH
    utils_list_push_back(&g_msg_list, (list_item_t *)msg);
#else
    msg_proc(msg);
#endif
}

uint32_t msg_mod_reg(mod_id_t mod_id, msg_tab_item_t *msg_tab)
{
    if (mod_id >= MOD_ID_BUTT) {
        return RET_CODE_MSG_ID_OVER;
    }

    if (msg_tab == NULL) {
        return RET_CODE_MSG_TAB_NULL;
    }

    g_msg_tab[mod_id] = msg_tab;
    return RET_CODE_SUCCESS;
}

#define _PRE_TEST_MSG 1
#ifdef _PRE_TEST_MSG
uint32_t demo_send_msg(mod_id_t src_mid, mod_id_t dst_mid, msg_id_t msg_id, uint32_t len)
{
    msg_t *msg = msg_alloc();
    if (msg == NULL) {
        return RET_CODE_PTR_NULL;
    }
    msg_head_t *head = &(msg->payload);
    head->src_mid = src_mid;
    head->dst_mid = dst_mid;
    head->msg_id = msg_id;
    head->len = len;
    msg_send(msg);
    return RET_CODE_SUCCESS;
}

void demo_app()
{    
}

#endif