#include "show_page.h"

lv_style_t show_style;
static void event_top_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    lv_indev_t* indev = lv_indev_get_act(); //获取输入设备
	if (indev == NULL)  return;
    lv_point_t   lv_point;
    lv_indev_get_point(indev, &lv_point);

    static bool down_flag = false;
    static int press_x;
    if (code == LV_EVENT_PRESSING ) //点击事件
    {
        if(!down_flag)
        {
            press_x = lv_point.x;
            down_flag = true;
        }
    }
    if (code == LV_EVENT_RELEASED  ) //点击事件
    {
        if((lv_point.x - press_x) > 80)
        {
            page_transition_to_page_name("main_page");
        }

        down_flag = false;
    }
}


void show_text_set_default_style(void)
{
    lv_style_init(&show_style);
    lv_style_set_bg_color(&show_style, BACK_COLOR);
    lv_style_set_radius(&show_style, 5);
    lv_style_set_border_width(&show_style, 3);
    lv_style_set_border_color(&show_style, MAIN_COLOR);
    lv_style_set_line_color(&show_style, MAIN_COLOR);
    lv_style_set_line_opa(&show_style, 40);
    lv_style_set_text_color(&show_style, MAIN_COLOR);
    lv_style_set_pad_left(&show_style, 0);
    lv_style_set_pad_right(&show_style, 0);
    lv_style_set_pad_top(&show_style, 5);
    lv_style_set_pad_bottom(&show_style, 5);
}

void show_page_init(struct page *page)
{
    show_text_set_default_style();

    lv_obj_t *body_obj = page->body_obj;

    lv_obj_t * top_obj = lv_obj_create(body_obj);
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
   
    lv_obj_t * label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "Show Product");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    lv_obj_t *bg_obj = lv_obj_create(body_obj);
    lv_obj_set_size(bg_obj, lv_obj_get_width(body_obj), lv_obj_get_height(body_obj) - 25);
    lv_obj_set_pos(bg_obj, 0, 25);
    lv_obj_add_style(bg_obj, &page_style, 0);
    // lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0xcccccc), 0);
    lv_obj_update_layout(bg_obj);
    lv_obj_clear_flag(bg_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t * show_img = lv_img_create(bg_obj);
	lv_img_set_src(show_img,&imgshow);
    lv_obj_align(show_img, LV_ALIGN_CENTER, 0, 0);
    lv_image_set_scale(show_img, 190);

}

void show_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
