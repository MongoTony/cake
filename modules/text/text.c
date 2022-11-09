/**
 * @file line.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils_comm.h"
#include "utils_log.h"
#include "text.h"

#define TEXT_FILE_NAME "./schedule.txt"
text_info_t *g_text_info = NULL;

//////////////////////////////////////////////////////////////////////////////////////
#if 1
text_info_t *text_alloc_text_info(char *file_full_name)
{
    log_print(0, 0, "enter,file=[%s]!", file_full_name);
    if (file_full_name == NULL) {
        log_print(0, 0, "file name is null.");
        return NULL;
    }

    if (strlen(file_full_name) <= 0) {
        log_print(0, 0, "file name len <= 0.");
        return NULL;
    }

    text_info_t *text_info = utils_malloc(sizeof(text_info_t));
    if (text_info == NULL) {
        log_print(0, 0, "utils_malloc fail!");
        return NULL;
    }

    memset(text_info, 0, sizeof(text_info_t));
    utils_list_init(&(text_info->line_list));

    memcpy(text_info->file_name, file_full_name, strlen(file_full_name));
    return text_info;
}

void text_free_text_info(text_info_t *text_info)
{
    log_print(0, 0, "enter!");
    if (text_info == NULL) {
        return;
    }

    utils_free(text_info);
}

static bool text_open_file(text_info_t *text_info)
{
    FILE *ptr_file = fopen(text_info->file_name, "r");
    if (ptr_file == NULL) {
        log_print(0, 0, "open file[%s] fails!", text_info->file_name);
        return false;
    }
    text_info->ptr_file = ptr_file;
    return true;
}

static void text_close_file(text_info_t *text_info)
{
    if (text_info->ptr_file != NULL) {
        fclose(text_info->ptr_file);
        text_info->ptr_file = NULL;
    }
    return;
}

uint32_t text_read_lines(text_info_t *text_info)
{

    if(text_info->ptr_file == NULL) {
        return -1;
    }

    uint32_t line_no = 0;
    while (!feof(text_info->ptr_file)) {
        line_info_t *line_info = (line_info_t *)utils_malloc(sizeof(line_info_t));
        if (line_info == NULL) {
            break;
        }
        if (fgets(line_info->str, MAX_LINE_CHAR_NUM, text_info->ptr_file) == NULL) {
            utils_free(line_info);
            break;
        }

        line_no++;
        line_info->line_seq = line_no;
        line_info->str_len = strlen(line_info->str);
        utils_list_push_back(&text_info->line_list, (list_item_t *)line_info);
    }

    return 0;
}

void *text_print_line_info(void *args)
{
    line_info_t *line_info = (line_info_t *)args;
    log_print_tab(0, 0, "[%.4u]%s", line_info->line_seq, line_info->str);
    // sleep(1);
    return NULL;
}

void text_print_lines(text_info_t *text_info)
{
    log_print(0, 0, "enter!");
    utils_list_travel(&text_info->line_list, text_print_line_info);
}

int text_init_text_info(text_info_t *text_info)
{
    if (text_info == NULL) {
        return -1;
    }

    if (!text_open_file(text_info)) {
        log_print(0, 0, "open file fail!");
        return -1;
    }

    if(text_read_lines(text_info) == -1) {
        return -1;
    }

    return 0;
}

void text_deinit_text_info(text_info_t *text_info)
{
    if (text_info == NULL) {
        return;
    }

    if (text_info->ptr_file != NULL) {
        text_close_file(text_info);
        text_info->ptr_file = NULL;        
    }

    utils_list_clear(&(text_info->line_list));
}
#endif
//////////////////////////////////////////////////////////////////////////////////////

int text_init(void)
{
    log_print(0, 0, "enter!");
    text_info_t *text_info = text_alloc_text_info(TEXT_FILE_NAME);
    if (text_info == NULL) {
        log_print(0, 0, "alloc fail!");
        return -1;
    }
    if(text_init_text_info(text_info) != 0) {
        log_print(0, 0, "int text_info fail!");
        return -1;
    }

    log_print(0, 0, "text_info[%p]!", text_info);
    g_text_info = text_info;
    return 0;
}

void text_deinit(void)
{
    text_deinit_text_info(g_text_info);
    text_free_text_info(g_text_info);
    g_text_info = NULL;
}

void text_show(void)
{
    log_print(0, 0, "enter!");
    if (g_text_info != NULL) {
        text_print_lines(g_text_info);
    }
}
