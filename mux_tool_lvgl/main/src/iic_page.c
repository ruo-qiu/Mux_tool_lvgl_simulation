#include "iic_page.h"

lv_style_t iic_style;
static lv_obj_t* iic_list;
uint8_t addr[5] = {0};
static void event_iic_switch_btn_handle(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    lv_obj_t* label = lv_obj_get_child(lv_event_get_target(e), 0);
    static bool is_sda_scl = true;
    if(code == LV_EVENT_CLICKED)   //点击事件
    {
        if(is_sda_scl)
        {
            lv_label_set_text(label, "sck "LV_SYMBOL_SHUFFLE" sda");
            is_sda_scl = false;
        }
        else
        {
            lv_label_set_text(label, "sda "LV_SYMBOL_SHUFFLE" sck");
            is_sda_scl = true;
        }
    }
}


static void event_iic_search_btn_handle(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    if(code == LV_EVENT_CLICKED)   //点击事件
    {
        addr[4] = addr[3];
        addr[3] = addr[2];
        addr[2] = addr[1];
        addr[1] = addr[0];
        addr[0] = lv_rand(1, 254);
        if(addr[0] != 0)
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 0), 1), "          0x%x", addr[0]);
        }
        else
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 0), 1), "          none");
        }
        if(addr[1] != 0)
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 1), 1), "          0x%x", addr[1]);
        }
        else
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 1), 1), "          none");
        }
        if(addr[2] != 0)
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 2), 1), "          0x%x", addr[2]);
        }
        else
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 2), 1), "          none");
        }
        if(addr[3] != 0)
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 3), 1), "          0x%x", addr[3]);
        }
        else
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 3), 1), "          none");
        }
        if(addr[4] != 0)
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 4), 1), "          0x%x", addr[4]);
        }
        else
        {
            lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 4), 1), "          none");
        }
    }
}


static void event_iic_clean_btn_handle(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    if(code == LV_EVENT_CLICKED)   //点击事件
    {
        memset(addr, 0, sizeof(addr));
        lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 0), 1), "          none");
        lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 1), 1), "          none");
        lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 2), 1), "          none");
        lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 3), 1), "          none");
        lv_label_set_text_fmt(lv_obj_get_child(lv_obj_get_child(iic_list, 4), 1), "          none");
    }
}

static void event_top_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    lv_indev_t* indev = lv_indev_get_act(); //获取输入设备
    if(indev == NULL)  return;
    lv_point_t   lv_point;
    lv_indev_get_point(indev, &lv_point);

    static bool down_flag = false;
    static int press_x;
    if(code == LV_EVENT_PRESSING)   //点击事件
    {
        if(!down_flag)
        {
            press_x = lv_point.x;
            down_flag = true;
        }
    }
    if(code == LV_EVENT_RELEASED)    //点击事件
    {
        if((lv_point.x - press_x) > 80)
        {
            page_transition_to_page_name("main_page");
        }

        down_flag = false;
    }
}

void iic_text_set_default_style(void)
{
    lv_style_init(&iic_style);
    lv_style_set_bg_color(&iic_style, BACK_COLOR);
    lv_style_set_radius(&iic_style, 5);
    lv_style_set_border_width(&iic_style, 3);
    lv_style_set_border_color(&iic_style, MAIN_COLOR);
    lv_style_set_line_color(&iic_style, MAIN_COLOR);
    lv_style_set_line_opa(&iic_style, 40);
    lv_style_set_text_color(&iic_style, MAIN_COLOR);
    lv_style_set_pad_left(&iic_style, 10);
    lv_style_set_pad_right(&iic_style, 10);
    lv_style_set_pad_top(&iic_style, 10);
    lv_style_set_pad_bottom(&iic_style, 10);
}
void iic_page_init(struct page* page)
{
    iic_text_set_default_style();

    lv_obj_t* body_obj = page->body_obj;

    lv_obj_t* top_obj = lv_obj_create(body_obj);
    lv_obj_add_event_cb(top_obj, event_top_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
    lv_obj_add_style(top_obj, &app_style, 0);
    lv_obj_set_size(top_obj, lv_obj_get_width(body_obj), 25);
    lv_obj_set_pos(top_obj, 0, -25);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, top_obj);
    lv_anim_set_values(&a, -25, 0);
    lv_anim_set_duration(&a, 500);
    lv_anim_set_exec_cb(&a, anim_y_cb);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
    lv_anim_start(&a);

    lv_obj_t* label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "IIC Search");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    lv_obj_t* list_obj = lv_obj_create(body_obj);
    lv_obj_add_style(list_obj, &app_style, 0);
    lv_obj_set_size(list_obj, 180, 160);
    lv_obj_align(list_obj, LV_ALIGN_LEFT_MID, 20, 10);

    lv_obj_t* label1 = lv_label_create(list_obj);
    lv_label_set_text(label1, "7bit address");
    lv_obj_align(label1,  LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_color(label1, BACK_COLOR, LV_PART_MAIN);

    iic_list = lv_list_create(list_obj);
    lv_obj_set_size(iic_list, 170, 130);
    lv_obj_align(iic_list, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_add_style(iic_list, &app_style, 0);
    lv_obj_t* btn;
    btn = lv_list_add_button(iic_list, LV_SYMBOL_LIST, "          none");
    lv_obj_add_style(btn, &iic_style, 0);
    btn = lv_list_add_button(iic_list, LV_SYMBOL_LIST, "          none");
    lv_obj_add_style(btn, &iic_style, 0);
    btn = lv_list_add_button(iic_list, LV_SYMBOL_LIST, "          none");
    lv_obj_add_style(btn, &iic_style, 0);
    btn = lv_list_add_button(iic_list, LV_SYMBOL_LIST, "          none");
    lv_obj_add_style(btn, &iic_style, 0);
    btn = lv_list_add_button(iic_list, LV_SYMBOL_LIST, "          none");
    lv_obj_add_style(btn, &iic_style, 0);

    lv_obj_t* iic_switch_btn = lv_btn_create(body_obj);
    lv_obj_set_size(iic_switch_btn, 80, 38);
    lv_obj_align_to(iic_switch_btn, list_obj, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);
    lv_obj_set_style_bg_color(iic_switch_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t* label2 = lv_label_create(iic_switch_btn);
    lv_label_set_text(label2, "sda "LV_SYMBOL_SHUFFLE" sck");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label2, BACK_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(iic_switch_btn, event_iic_switch_btn_handle, LV_EVENT_ALL, NULL);

    lv_obj_t* iic_search_btn = lv_btn_create(body_obj);
    lv_obj_set_size(iic_search_btn, 80, 38);
    lv_obj_align_to(iic_search_btn, list_obj, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_set_style_bg_color(iic_search_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t* label3 = lv_label_create(iic_search_btn);
    lv_label_set_text(label3, "Search");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label3, BACK_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(iic_search_btn, event_iic_search_btn_handle, LV_EVENT_ALL, NULL);

    lv_obj_t* iic_clean_btn = lv_btn_create(body_obj);
    lv_obj_set_size(iic_clean_btn, 80, 38);
    lv_obj_align_to(iic_clean_btn, list_obj, LV_ALIGN_OUT_RIGHT_BOTTOM, 20, 0);
    lv_obj_set_style_bg_color(iic_clean_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t* label4 = lv_label_create(iic_clean_btn);
    lv_label_set_text(label4, "Clean");
    lv_obj_align(label4, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label4, BACK_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(iic_clean_btn, event_iic_clean_btn_handle, LV_EVENT_ALL, NULL);
}

void iic_page_exit(struct page* old_page, struct page* new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
