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
#if 1
#define log_print(mid, level, fmt, args...) printf("%-45s %05d" "%+25s : " fmt "\r\n", __FILE__, __LINE__, __FUNCTION__, ##args)
#else
#define log_print(mid, level, fmt, args...)
#endif
#define log_print_tab(mid, level, fmt, args...) printf(fmt "", ##args)

#endif