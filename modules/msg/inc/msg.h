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


typedef enum {
    MOD_ID_WIFI,
    MOD_ID_BLE,
    MOD_ID_NFC,

    MOD_ID_BUTT
} mod_id_t;

typedef enum { 
    MSG_ID_WIFI_BASE = 0x100,

    MSG_ID_BLE_BASE = 0x200,

    MSG_ID_NFC_BASE = 0x300,

    MSG_ID_BUTT = 0xFFFF

} msg_id_t;

typedef struct {
    list_item_t *next;
    mod_id_t src_mid;
    mod_id_t dst_mid;
    msg_id_t msg_id;

    uint8_t data[0];
} msg_t;

int msg_init(void);
int msg_exit(void);

#endif