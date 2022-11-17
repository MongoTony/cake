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

#ifndef DATA_H
#define DATA_H

#include <stdint.h>

#define MAX_DATA_CHAN_SIZE 10

typedef int (data_chan_cb_t)(void *);

typedef struct {

    data_chan_cb_t *cb;

} data_chan_t;

int data_init(void);
int data_exit(void);
#endif