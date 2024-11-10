#ifndef __IIC_PAGE__
#define __IIC_PAGE__

#include "lvgl_page_ctrl.h"


void iic_page_init(struct page *page);
void iic_page_exit(struct page *old_page, struct page *new_page);

#endif
