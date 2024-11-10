#ifndef __MAIN_PAGE__
#define __MAIN_PAGE__

#include "lvgl_page_ctrl.h"

typedef struct app
{
    char name[32];                                                      // app名
    lv_obj_t * btn;                                                     // app按键
    lv_obj_t * label;                                                   // app标签
    lv_style_t *app_style;                                              // app风格
    const void * img;                                                   // app图标
    void (*callback)(lv_event_t* e);                                    // 绑定回调函数
}app_struct;
void app_set_default_style(void);
void main_page_init(struct page *page);
void main_page_exit(struct page *old_page, struct page *new_page);

#endif
