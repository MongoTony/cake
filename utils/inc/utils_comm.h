/**
 * @file utils_comm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILS_COMM_H
#define UTILS_COMM_H

#include <stdlib.h>

#define stat_inc(val) {++val;}
#define stat_dec(val) {--val;}

#define utils_malloc(len) malloc((size_t)(len))
#define utils_free(p)    free((void*)p)

#endif
