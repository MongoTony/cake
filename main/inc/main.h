/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

typedef int (*op_func_t)(void);

typedef struct {
    uint32_t fid;
    op_func_t func;
}op_act_info_t;

#endif