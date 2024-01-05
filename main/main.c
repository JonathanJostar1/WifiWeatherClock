/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "net_task.h"
#include "ui_task.h"
#include "port_delay.h"
#include "bsp_config.h"

static TaskHandle_t net_task_handle;
static TaskHandle_t ui_task_handle;

void app_main(void)
{
    bsp_config();

    xTaskCreate(ui_task,  "ui_task",  5 * 1024,  NULL, 3, &ui_task_handle);
    xTaskCreate(net_task, "net_task", 5 * 1024,   NULL, 2, &net_task_handle);

    while(1)
    {
        delay_ms(1000);
    }
}
