/**
 * @file text.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdint.h>
#include "utils_list.h"

#define MAX_TEXT_NAME_SIZE 256
#define MAX_LINE_CHAR_NUM 120

typedef struct {
    list_item_t *next;

    uint32_t line_seq;
    uint32_t str_len;
    char str[MAX_LINE_CHAR_NUM];
} line_info_t;

typedef struct {
    char file_name[MAX_TEXT_NAME_SIZE];
    FILE *ptr_file;

    utils_list_t line_list;
} text_info_t;

int text_init(void);
void text_deinit(void);
void text_show(void);

#endif
