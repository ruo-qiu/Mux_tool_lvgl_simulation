#include "lvgl_page_ctrl.h"

uint16_t show_img[256*240];
page_struct page_admin[MAX_PAGE_NUM];	// 存储所有创建好的页面
int page_num = 0;			            // 记录 page_admin[] 数组中存在多少个页面
page_struct* cur_page;				    // 记录当前显示的页面
lv_style_t page_style;                  // 默认页面背景样式

// 描述：设置页面默认样式
// 参数：空
// 返回：空
void page_set_default_style(void)
{
    lv_style_init(&page_style);
    lv_style_set_bg_color(&page_style, BACK_COLOR);
    lv_style_set_radius(&page_style, 0);
    lv_style_set_pad_all(&page_style, 0);
    lv_style_set_border_side(&page_style, LV_BORDER_SIDE_NONE);
}

// 描述：设置初始化页面
// 参数：空
// 返回：页面控件指针
lv_obj_t* page_set_default_screen(void)
{
    lv_obj_t* main_obj = lv_obj_create(NULL);
    lv_obj_clean(main_obj);
    lv_obj_add_style(main_obj, &page_style, 0);
    return main_obj;
}

// 描述：通过名字寻找指定页面
// 参数：空
// 返回：页面对象指针
page_struct* page_search_from_name(char* page_name)
{
    for(int i = 0; i < page_num; i++)
    {
        if(strcmp(page_admin[i].name, page_name) == 0)
        {
            return &page_admin[i];
        }
    }
    return NULL;
}

// 描述：切换指定名字页面
// 参数：空
// 返回：0为成功 -1为失败
int page_transition_to_page_name(char* new_page_name)
{
    if(strcmp(new_page_name, "") == 0 || new_page_name == NULL)
    {
        return -1;
    }

    page_struct* new_page = page_search_from_name(new_page_name);
    if(new_page != NULL)
    {
        cur_page->page_exit(cur_page, new_page);
        new_page->page_init(new_page);
        cur_page = new_page;
        return 0;
    }
    else
    {
        return -1;
    }
}

// 描述：切换上一优先级页面
// 参数：空
// 返回：页面对象指针
page_struct* page_return_prev_page(page_struct* new_page)
{
    if(new_page == NULL)
    {
        return NULL;
    }
    int cur_page_level = new_page->page_level;
    for(int i = page_num - 1; i >= 0; i--)
    {
        if(page_admin[i].page_level < cur_page_level)
        {
            return &page_admin[i];
        }
    }
    return NULL;
}

// 描述：创建页面
// 参数：page_name          页面名字
// 参数：default_screen     创建初始页面屏幕
// 参数：page_level         页面优先级 0最低
// 参数：page_init          页面初始化函数
// 参数：page_exit          页面退出函数
// 参数：is_active          页面是否激活
// 返回：空
void page_create_new_page(char* page_name,
                          lv_obj_t* (*default_screen)(void),
                          int page_level,
                          void (*page_init)(page_struct* page),
                          void (*page_exit)(page_struct* old_page, page_struct* new_page),
                          int is_active)
{
    if(page_num >= MAX_PAGE_NUM)
    {
        return;
    }
    strcpy(page_admin[page_num++].name, page_name);
    page_admin[page_num - 1].body_obj = default_screen();
    page_admin[page_num - 1].page_level = page_level;
    page_admin[page_num - 1].page_init = page_init;
    page_admin[page_num - 1].page_exit = page_exit;
    if(is_active)
    {
        cur_page = &page_admin[page_num - 1];
        lv_scr_load(page_admin[page_num - 1].body_obj);		// 设置该页面为第一个显示在屏幕上面的页面
        // lv_scr_load_anim(page_admin[page_num - 1].body_obj, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
        cur_page->page_init(cur_page);
    }
}


void anim_x_cb(void* var, int32_t v)
{
    lv_obj_set_x(var, v);
}
void anim_y_cb(void* var, int32_t v)
{
    lv_obj_set_y(var, v);
}
