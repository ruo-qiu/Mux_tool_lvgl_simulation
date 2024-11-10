#ifndef __NES_PAGE__
#define __NES_PAGE__

#include "lvgl_page_ctrl.h"


void nes_page_init(struct page *page);
void nes_page_exit(struct page *old_page, struct page *new_page);

#endif