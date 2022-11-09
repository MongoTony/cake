/**
 * @file utils_log.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <stdio.h>

#define log_print(mid, level, fmt, args...) printf("[%s]::" fmt "\r\n", __FUNCTION__, ##args)

#define log_print_tab(mid, level, fmt, args...) printf(fmt "\r\n", ##args)

#endif