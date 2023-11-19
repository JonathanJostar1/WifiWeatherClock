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

static TaskHandle_t net_task_handle;

void app_main(void)
{
    xTaskCreate(net_task, "net_task", 5*1024, NULL, 2, &net_task_handle);
}
