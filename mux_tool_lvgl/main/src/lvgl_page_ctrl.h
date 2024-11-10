#ifndef __LVGL_PAGE_CTRL__
#define __LVGL_PAGE_CTRL__

#include "lvgl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "nes_main.h"

#define MAX_PAGE_NUM    20
typedef struct page
{
    char name[32];                                                      // 页面名
    int page_level;                                                     // 页面等级，依靠这个来实现对上一页面的切换，该值越小，等级越高
    lv_obj_t* body_obj;                                                 // 页面结构体
    void* private_data;                                                 // 私有数据
    void (*page_init)(struct page* page);                               // 创建页面函数
    void (*page_exit)(struct page* old_page, struct page* new_page);    // 销毁页面函数
} page_struct;

#define MAIN_COLOR  lv_color_hex(0xc0d070)
#define BACK_COLOR  lv_color_hex(0x2a363b)

LV_IMG_DECLARE(imgimage);
LV_IMG_DECLARE(imgruo);
LV_IMG_DECLARE(imgshiboq);
LV_IMG_DECLARE(imguart);
LV_IMG_DECLARE(imgiicsearch);
LV_IMG_DECLARE(imgusbmk);
LV_IMG_DECLARE(imggame2048);
LV_IMG_DECLARE(imgmic);
LV_IMG_DECLARE(imghot);
LV_IMG_DECLARE(imgnet);
LV_IMG_DECLARE(imgsignal);
LV_IMG_DECLARE(imgelec);
LV_IMG_DECLARE(imggame);
LV_IMG_DECLARE(imgenter);
LV_IMG_DECLARE(imgshow);
LV_IMG_DECLARE(imgself);

//extern fifo_struct         uart_receiver_fifo;                             //
//extern uint8_t             uart_receiver_buffer[1000];         // 数据存放数组
extern uint8_t      keysend;
extern uint16_t    show_img[256*240];
extern int16_t     mic_data[64];
extern uint8_t     uart_get_data;
extern struct      page page_admin[MAX_PAGE_NUM];	                            // 存储所有创建好的页面
extern int         page_num;			                                        // 记录 page_admin[] 数组中存在多少个页面
extern page_struct* cur_page;				                                    // 记录当前显示的页面
extern lv_style_t  page_style;                                                 // 默认页面背景样式
extern lv_style_t app_style;                                            // 默认app背景样式
void        page_set_default_style(void);
lv_obj_t*   page_set_default_screen(void);
page_struct* page_search_from_name(char* page_name);
int         page_transition_to_page_name(char* new_page_name);
page_struct* page_return_prev_page(page_struct* new_page);
void        page_create_new_page(char* page_name,
                                 lv_obj_t* (*default_screen)(void),
                                 int page_level,
                                 void (*page_init)(page_struct* page),
                                 void (*page_exit)(page_struct* old_page,
                                         page_struct* new_page),
                                 int is_active);

void anim_x_cb(void* var, int32_t v);
void anim_y_cb(void* var, int32_t v);

#endif
