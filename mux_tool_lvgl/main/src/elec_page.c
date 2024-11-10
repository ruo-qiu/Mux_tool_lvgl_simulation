#include "elec_page.h"

lv_obj_t* elec_chart;
lv_chart_series_t* elec_ser;
lv_obj_t* elec_cale_left;

lv_obj_t* elec_cur_obj;
lv_obj_t* elec_cur_label;
lv_obj_t* elec_volt_obj;
lv_obj_t* elec_volt_label;
lv_obj_t* elec_pow_obj;
lv_obj_t* elec_pow_label;

lv_style_t elec_style;
lv_timer_t* elec_timer;
const char* elec_defaultlabels[] = {"0 ", "1 ", "2 ", NULL};

void elec_timer_handle(lv_timer_t* timer)
{
    uint16_t cur = lv_rand(90,110);
    uint16_t volt = lv_rand(450,500);
    uint16_t pow = cur * volt / 100;
    lv_chart_set_next_value(elec_chart, elec_ser, (uint16_t)cur);
    lv_label_set_text_fmt(elec_cur_label, "%d.%d", cur / 100, cur %100);
    lv_label_set_text_fmt(elec_volt_label, "%d.%d", volt / 100, volt %100);
    lv_label_set_text_fmt(elec_pow_label, "%d.%d", pow / 100, pow %100);
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

void elec_chart_set_default_style(void)
{
    lv_style_init(&elec_style);
    lv_style_set_bg_color(&elec_style, BACK_COLOR);
    lv_style_set_radius(&elec_style, 5);
    lv_style_set_border_width(&elec_style, 3);
    lv_style_set_border_color(&elec_style, MAIN_COLOR);
    lv_style_set_line_color(&elec_style, MAIN_COLOR);
    lv_style_set_line_opa(&elec_style, 40);
    lv_style_set_text_color(&elec_style, MAIN_COLOR);

    // lv_style_set_bg_grad_color(&elec_style, MAIN_COLOR);
    // lv_style_set_arc_color
    
}

void elec_page_init(struct page* page)
{
    elec_chart_set_default_style();
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
    lv_label_set_text(label0, "Power Meter");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);


    elec_timer = lv_timer_create(elec_timer_handle, 100,  NULL);

    elec_chart = lv_chart_create(body_obj);
    lv_obj_set_size(elec_chart, 180, 160);
    lv_obj_align(elec_chart, LV_ALIGN_LEFT_MID, 30, 10);
    lv_obj_add_style(elec_chart, &elec_style, 0);
    lv_chart_set_point_count(elec_chart, 128);
    lv_chart_set_type(elec_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(elec_chart, 5, 5);
    lv_chart_set_range(elec_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);
    elec_ser = lv_chart_add_series(elec_chart, MAIN_COLOR, LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_width(elec_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_height(elec_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(elec_chart, 2, LV_PART_ITEMS);
    lv_chart_set_all_value(elec_chart, elec_ser, 0);

    elec_cale_left = lv_scale_create(body_obj);
    lv_scale_set_mode(elec_cale_left, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_size(elec_cale_left, 10, 140);
    lv_obj_set_style_length(elec_cale_left, 5, LV_PART_INDICATOR);
    lv_obj_set_style_length(elec_cale_left, 3, LV_PART_ITEMS);

    lv_obj_set_style_line_color(elec_cale_left, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_set_style_line_color(elec_cale_left, MAIN_COLOR, LV_PART_ITEMS);
    lv_obj_set_style_line_color(elec_cale_left, MAIN_COLOR, LV_PART_INDICATOR);
    lv_obj_set_style_text_color(elec_cale_left, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(elec_cale_left, MAIN_COLOR, LV_PART_ITEMS);
    lv_scale_set_total_tick_count(elec_cale_left, 9);
    lv_scale_set_major_tick_every(elec_cale_left, 4);
    lv_scale_set_range(elec_cale_left, 0, 5);
    lv_scale_set_label_show(elec_cale_left, true);
    // lv_obj_set_style_pad_hor(elec_cale_left, lv_chart_get_first_point_center_offset(elec_chart), 0);
    lv_obj_align_to(elec_cale_left, elec_chart, LV_ALIGN_OUT_LEFT_MID, 1, 0);
    lv_scale_set_text_src(elec_cale_left, (const char**)elec_defaultlabels);

    elec_cur_obj = lv_obj_create(body_obj);
    lv_obj_set_size(elec_cur_obj, 85, 40);
    lv_obj_align_to(elec_cur_obj, elec_chart, LV_ALIGN_OUT_RIGHT_TOP, 12, 0);
    lv_obj_add_style(elec_cur_obj, &elec_style, 0);
    lv_obj_clear_flag(elec_cur_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* elec_cur_obj1 = lv_obj_create(body_obj);
    lv_obj_set_size(elec_cur_obj1, 30, 40);
    lv_obj_align_to(elec_cur_obj1, elec_chart, LV_ALIGN_OUT_RIGHT_TOP, 12, 0);
    lv_obj_add_style(elec_cur_obj1, &elec_style, 0);
    lv_obj_set_style_pad_all(elec_cur_obj1, 0, LV_PART_MAIN);
    lv_obj_clear_flag(elec_cur_obj1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* label1 = lv_label_create(elec_cur_obj1);
    lv_label_set_text(label1, "C");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label1, MAIN_COLOR, LV_PART_MAIN);
    elec_cur_label = lv_label_create(elec_cur_obj);
    lv_label_set_text(elec_cur_label, "0.20");
    lv_obj_align(elec_cur_label, LV_ALIGN_CENTER, 12, 0);
    lv_obj_set_style_text_color(elec_cur_label, MAIN_COLOR, LV_PART_MAIN);
    
    elec_volt_obj = lv_obj_create(body_obj);
    lv_obj_set_size(elec_volt_obj, 85, 40);
    lv_obj_align_to(elec_volt_obj, elec_chart, LV_ALIGN_OUT_RIGHT_MID, 12, 0);
    lv_obj_add_style(elec_volt_obj, &elec_style, 0);
    lv_obj_clear_flag(elec_volt_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* elec_volt_obj1 = lv_obj_create(body_obj);
    lv_obj_set_size(elec_volt_obj1, 30, 40);
    lv_obj_align_to(elec_volt_obj1, elec_chart, LV_ALIGN_OUT_RIGHT_MID, 12, 0);
    lv_obj_add_style(elec_volt_obj1, &elec_style, 0);
    lv_obj_set_style_pad_all(elec_volt_obj1, 0, LV_PART_MAIN);
    lv_obj_clear_flag(elec_volt_obj1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* label2 = lv_label_create(elec_volt_obj1);
    lv_label_set_text(label2, "V");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label2, MAIN_COLOR, LV_PART_MAIN);
    elec_volt_label = lv_label_create(elec_volt_obj);
    lv_label_set_text(elec_volt_label, "5.00");
    lv_obj_align(elec_volt_label, LV_ALIGN_CENTER, 12, 0);
    lv_obj_set_style_text_color(elec_volt_label, MAIN_COLOR, LV_PART_MAIN);

    
    elec_pow_obj = lv_obj_create(body_obj);
    lv_obj_set_size(elec_pow_obj, 85, 40);
    lv_obj_align_to(elec_pow_obj, elec_chart, LV_ALIGN_OUT_RIGHT_BOTTOM, 12, 0);
    lv_obj_add_style(elec_pow_obj, &elec_style, 0);
    lv_obj_clear_flag(elec_pow_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* elec_pow_obj1 = lv_obj_create(body_obj);
    lv_obj_set_size(elec_pow_obj1, 30, 40);
    lv_obj_align_to(elec_pow_obj1, elec_chart, LV_ALIGN_OUT_RIGHT_BOTTOM, 12, 0);
    lv_obj_add_style(elec_pow_obj1, &elec_style, 0);
    lv_obj_set_style_pad_all(elec_pow_obj1, 0, LV_PART_MAIN);
    lv_obj_clear_flag(elec_pow_obj1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* label3 = lv_label_create(elec_pow_obj1);
    lv_label_set_text(label3, "P");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label3, MAIN_COLOR, LV_PART_MAIN);
    elec_pow_label = lv_label_create(elec_pow_obj);
    lv_label_set_text(elec_pow_label, "5.20");
    lv_obj_align(elec_pow_label, LV_ALIGN_CENTER, 12, 0);
    lv_obj_set_style_text_color(elec_pow_label, MAIN_COLOR, LV_PART_MAIN);

    // ina226_init();
}

void elec_page_exit(struct page* old_page, struct page* new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_timer_delete(elec_timer);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
