#ifndef __SIGNAL_PAGE__
#define __SIGNAL_PAGE__

#include "lvgl_page_ctrl.h"


void signal_page_init(struct page *page);
void signal_page_exit(struct page *old_page, struct page *new_page);

#endif