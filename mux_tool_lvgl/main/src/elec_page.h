#ifndef __ELEC_PAGE__
#define __ELEC_PAGE__

#include "lvgl_page_ctrl.h"


void elec_page_init(struct page *page);
void elec_page_exit(struct page *old_page, struct page *new_page);

#endif