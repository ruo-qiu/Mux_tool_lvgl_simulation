#ifndef __USBMK_PAGE__
#define __USBMK_PAGE__

#include "lvgl_page_ctrl.h"


void usbmk_page_init(struct page *page);
void usbmk_page_exit(struct page *old_page, struct page *new_page);

#endif