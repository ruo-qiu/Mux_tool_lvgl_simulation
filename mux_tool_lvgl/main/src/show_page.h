#ifndef __SHOW_PAGE__
#define __SHOW_PAGE__

#include "lvgl_page_ctrl.h"


void show_page_init(struct page *page);
void show_page_exit(struct page *old_page, struct page *new_page);

#endif