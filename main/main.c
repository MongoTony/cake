/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "foo.h"
#include "data_rx.h"
#include "schedule.h"
#include "main.h"

op_act_info_t g_init_func[10] = {
    [0] = {0, schedule_init},
    [1] = {0, NULL}
};

op_act_info_t g_exit_func[10] = {
    [0] = {0, schedule_exit},
    [1] = {0, NULL}
};

int sys_op_fn(op_act_info_t *op_act)
{
    while (op_act->func != NULL) {
        op_act->func();
        op_act++;
    }
}

int main(char* argc, char** argv) {

    sys_op_fn(g_init_func);

    schedule_run();

    int num;
    while (scanf("%d", &num) != 0)
    {
        if (num == 0) {
            break;;
        }
    }

    sys_op_fn(g_exit_func);
    return 0;
}
