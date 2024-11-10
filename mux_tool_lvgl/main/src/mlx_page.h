#ifndef __MLX_PAGE__
#define __MLX_PAGE__

#include "lvgl_page_ctrl.h"


void mlx_page_init(struct page *page);
void mlx_page_exit(struct page *old_page, struct page *new_page);

#endif