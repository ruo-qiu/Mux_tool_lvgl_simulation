#ifndef __UART_PAGE__
#define __UART_PAGE__

#include "lvgl_page_ctrl.h"

void uart_page_init(struct page *page);
void uart_page_exit(struct page *old_page, struct page *new_page);

#endif