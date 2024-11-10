#ifndef __OSC_PAGE__
#define __OSC_PAGE__

#include "lvgl_page_ctrl.h"


void osc_page_init(struct page *page);
void osc_page_exit(struct page *old_page, struct page *new_page);

#endif