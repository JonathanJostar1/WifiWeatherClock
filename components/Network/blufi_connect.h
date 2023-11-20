#ifndef  __BLUFI_CONNECT_H_
#define  __BLUFI_CONNECT_H_

#include "esp_blufi_api.h"

/* 初始化wifi */
int initialise_wifi(void);

/* 初始化blufi */
int blufi_init(void);

/* 去初始化blufi */
int blufi_deinit(void);

#endif
