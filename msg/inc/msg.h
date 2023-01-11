/**
 * @file document.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MSG_H
#define MSG_H

#include "utils_list.h"

#define MAX_MSG_DATA_SIZE 300
typedef enum {
    MOD_ID_A,
    MOD_ID_B,

    MOD_ID_BUTT
} mod_id_t;

typedef enum {
    MSG_ID_A_BASE = 0x100,
    MSG_ID_B_BASE = 0x200,

    MSG_ID_BUTT = 0xFFFF
} msg_id_t;

typedef struct {
    mod_id_t src_mid;
    mod_id_t dst_mid;
    msg_id_t msg_id;

    uint32_t len;
    uint8_t data[MAX_MSG_DATA_SIZE];
} msg_head_t;

typedef struct {
    list_item_t *next;
    msg_head_t payload;
} msg_t;

typedef uint32_t (*msg_op_t)(msg_head_t *);
typedef struct {
    mod_id_t mod_id_src;
    mod_id_t mod_id_dst;
    msg_id_t msg_id;
    msg_op_t *op;
} msg_tab_item_t;

int msg_init(void);
int msg_exit(void);
uint32_t msg_mod_reg(mod_id_t mod_id, msg_tab_item_t *msg_tab);
#endif