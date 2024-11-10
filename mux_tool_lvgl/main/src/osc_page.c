#include "osc_page.h"

lv_obj_t* osc_chart;
lv_obj_t* led_obj;
lv_chart_series_t* osc_ser;
lv_obj_t* scale_left;
lv_style_t osc_style;
lv_style_t roller_style;
lv_timer_t* timer;
int point_start = 0;
int MAX_POINT_X = 100;
bool is_show_wav = true;

void my_timer(lv_timer_t* timer)
{
    if(is_show_wav)
    {
        // lv_chart_set_next_value(osc_chart, osc_ser, (uint16_t)(ina226_getbusv() * 100.));
        point_start--;
        if(point_start < -MAX_POINT_X)
        {
            point_start += MAX_POINT_X;
        }
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
    if(code == LV_EVENT_CLICKED)
    {
        if(is_show_wav)
        {
            lv_obj_set_style_bg_color(led_obj, lv_color_hex(0xff0000), LV_PART_MAIN);
            is_show_wav = false;
        }
        else
        {
            lv_obj_set_style_bg_color(led_obj, lv_color_hex(0x00ff00), LV_PART_MAIN);
            is_show_wav = true;
        }
    }
}

static void chart_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* chart = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_invalidate(chart);
    }
    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE)
    {
        int32_t* s = lv_event_get_param(e);
        *s = LV_MAX(*s, 20);
    }
    else if(code == LV_EVENT_DRAW_POST_END)
    {
        int32_t id = lv_chart_get_pressed_point(chart);
        if(id == LV_CHART_POINT_NONE)
        {
            return;
        }
        lv_chart_series_t* ser = lv_chart_get_series_next(chart, NULL);
        while(ser)
        {
            lv_point_t p;
            lv_chart_get_point_pos_by_id(chart, ser, id, &p);
            int32_t* y_array = lv_chart_get_y_array(chart, ser);
            int32_t value = 0;
            int num = id - point_start;
            num = num % MAX_POINT_X;
            if((id - point_start) >= 0)
            {
                value = y_array[num];
            }

            char buf[16];
            lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY"%d.%d%d", (int)value / 100, (int)value % 100 / 10, (int)value % 100 % 10);

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);
            draw_rect_dsc.bg_color = lv_color_black();
            draw_rect_dsc.bg_opa = LV_OPA_50;
            draw_rect_dsc.radius = 3;
            draw_rect_dsc.bg_image_src = buf;
            draw_rect_dsc.bg_image_recolor = lv_color_white();

            lv_area_t a;
            a.x1 = chart->coords.x1 + p.x - 20;
            a.x2 = chart->coords.x1 + p.x + 20;
            a.y1 = chart->coords.y1 + p.y - 30;
            a.y2 = chart->coords.y1 + p.y - 10;

            lv_layer_t* layer = lv_event_get_layer(e);
            lv_draw_rect(layer, &draw_rect_dsc, &a);

            ser = lv_chart_get_series_next(chart, ser);
        }
    }
    else if(code == LV_EVENT_RELEASED)
    {
        lv_obj_invalidate(chart);
    }
}


const char* defaultlabels[] = {"0 ", "2.5", "5 ", NULL};
static char* custom_labels[] = {"0 ", "2.5", "5 ", NULL};
static char up_label[4] = {'0', ' ', 0};
static char mid_label[4] = {'0', '.', '0', 0};
static void osc_roller_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    char buf[32];
    uint16_t value = 0;
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        value = atoi(buf);
        lv_chart_set_range(osc_chart, LV_CHART_AXIS_PRIMARY_Y, 0, value * 100);

        mid_label[0] = (char)((value / 2) + 48);
        mid_label[2] = (char)(value * 100 / 2 % 100 / 10 + 48);

        if(value >= 10)
        {
            up_label[0] = (char)(value / 10 + 48);
            up_label[1] = (char)(value % 10 + 48);
        }
        else
        {
            up_label[0] = (char)(value % 10 + 48);
            up_label[1] = ' ';
        }

        custom_labels[1] = mid_label;
        custom_labels[2] = up_label;

        lv_scale_set_range(scale_left, 0, value);
        lv_scale_set_text_src(scale_left, (const char**)custom_labels);
    }
}

static void point_roller_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    char buf[32];
    uint16_t value = 0;
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        value = atoi(buf);
        LV_LOG_USER("Selected month: %d\n", value);
        MAX_POINT_X = value;
        point_start = MAX_POINT_X;

        lv_chart_set_point_count(osc_chart, MAX_POINT_X);
        lv_chart_set_all_value(osc_chart, osc_ser, 0);
    }
}

void osc_chart_set_default_style(void)
{
    lv_style_init(&osc_style);
    lv_style_set_bg_color(&osc_style, BACK_COLOR);
    lv_style_set_radius(&osc_style, 5);
    lv_style_set_border_width(&osc_style, 3);
    lv_style_set_border_color(&osc_style, MAIN_COLOR);
    lv_style_set_line_color(&osc_style, MAIN_COLOR);
    lv_style_set_line_opa(&osc_style, 40);
    lv_style_set_text_color(&osc_style, MAIN_COLOR);
    // lv_style_set_bg_grad_color(&osc_style, MAIN_COLOR);
    // lv_style_set_arc_color
}

void osc_roller_set_default_style(void)
{
    lv_style_init(&roller_style);
    lv_style_set_bg_color(&roller_style, BACK_COLOR);
    lv_style_set_radius(&roller_style, 5);
    lv_style_set_border_width(&roller_style, 3);
    lv_style_set_border_color(&roller_style, MAIN_COLOR);
    lv_style_set_text_color(&roller_style, MAIN_COLOR);
    lv_style_set_pad_all(&roller_style, 0);
}

void osc_page_init(struct page* page)
{
    osc_chart_set_default_style();
    osc_roller_set_default_style();
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
    lv_label_set_text(label0, "OscilloScopes");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    led_obj = lv_obj_create(top_obj);
    lv_obj_set_size(led_obj, 18, 18);
    lv_obj_set_style_bg_color(led_obj, lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_pad_all(led_obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(led_obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(led_obj, 10, LV_PART_MAIN);
    lv_obj_add_event_cb(led_obj, event_top_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/

    lv_obj_align(led_obj, LV_ALIGN_RIGHT_MID, -10, 0);


    timer = lv_timer_create(my_timer, 100,  NULL);

    osc_chart = lv_chart_create(body_obj);
    lv_obj_set_size(osc_chart, 220, 160);
    lv_obj_align(osc_chart, LV_ALIGN_LEFT_MID, 30, 10);
    lv_obj_add_style(osc_chart, &osc_style, 0);
    lv_chart_set_point_count(osc_chart, MAX_POINT_X);
    // lv_obj_set_style_bg_color(osc_chart, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_SCROLLBAR);
    lv_obj_add_event_cb(osc_chart, chart_event_cb, LV_EVENT_ALL, NULL);
    lv_chart_set_type(osc_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(osc_chart, 5, 5);
    lv_chart_set_range(osc_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 500);
    // lv_chart_set_axis_tick(osc_chart, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 4, 2, true, 40);
    osc_ser = lv_chart_add_series(osc_chart, MAIN_COLOR, LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_width(osc_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_height(osc_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(osc_chart, 2, LV_PART_ITEMS);
    lv_chart_set_all_value(osc_chart, osc_ser, 0);

    scale_left = lv_scale_create(body_obj);
    lv_scale_set_mode(scale_left, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_size(scale_left, 10, 140);
    lv_obj_set_style_length(scale_left, 5, LV_PART_INDICATOR);
    lv_obj_set_style_length(scale_left, 3, LV_PART_ITEMS);

    lv_obj_set_style_line_color(scale_left, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_set_style_line_color(scale_left, MAIN_COLOR, LV_PART_ITEMS);
    lv_obj_set_style_line_color(scale_left, MAIN_COLOR, LV_PART_INDICATOR);
    lv_obj_set_style_text_color(scale_left, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(scale_left, MAIN_COLOR, LV_PART_ITEMS);
    lv_scale_set_total_tick_count(scale_left, 9);
    lv_scale_set_major_tick_every(scale_left, 4);
    lv_scale_set_range(scale_left, 0, 5);
    lv_scale_set_label_show(scale_left, true);
    // lv_obj_set_style_pad_hor(scale_left, lv_chart_get_first_point_center_offset(osc_chart), 0);
    lv_obj_align_to(scale_left, osc_chart, LV_ALIGN_OUT_LEFT_MID, 1, 0);
    lv_scale_set_text_src(scale_left, (const char**)defaultlabels);

    lv_obj_t* osc_roller = lv_roller_create(body_obj);
    lv_obj_set_size(osc_roller, 50, 50);
    lv_obj_set_scrollbar_mode(osc_roller, LV_SCROLLBAR_MODE_OFF);
    lv_obj_align_to(osc_roller, osc_chart, LV_ALIGN_OUT_RIGHT_MID, 10, -32);
    lv_obj_add_style(osc_roller, &roller_style, 0);
    lv_obj_set_style_bg_color(osc_roller, BACK_COLOR, LV_PART_SELECTED);
    lv_obj_set_style_text_color(osc_roller, MAIN_COLOR, LV_PART_SELECTED);
    lv_obj_set_style_text_opa(osc_roller, 100, LV_PART_MAIN);
    lv_obj_set_style_text_opa(osc_roller, 255, LV_PART_SELECTED);
    lv_obj_set_style_text_line_space(osc_roller, 4, LV_PART_MAIN);
    lv_obj_add_event_cb(osc_roller, osc_roller_handler, LV_EVENT_ALL, NULL);
    lv_roller_set_options(osc_roller,
                          "2\n"
                          "3\n"
                          "4\n"
                          "5\n"
                          "6\n"
                          "7\n"
                          "8\n"
                          "9\n"
                          "10\n"
                          "11\n"
                          "12\n"
                          "13",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_selected(osc_roller, 3, LV_ANIM_ON);

    lv_obj_t* label1 = lv_label_create(body_obj);
    lv_label_set_text(label1, "Volt");
    lv_obj_align_to(label1, osc_roller, LV_ALIGN_OUT_TOP_MID, 0, -5);
    lv_obj_set_style_text_color(label1, MAIN_COLOR, LV_PART_MAIN);

    lv_obj_t* point_roller = lv_roller_create(body_obj);
    lv_obj_set_size(point_roller, 50, 50);
    lv_obj_set_scrollbar_mode(point_roller, LV_SCROLLBAR_MODE_OFF);
    lv_obj_align_to(point_roller, osc_chart, LV_ALIGN_OUT_RIGHT_MID, 10, 54);
    lv_obj_add_style(point_roller, &roller_style, 0);
    lv_obj_set_style_bg_color(point_roller, BACK_COLOR, LV_PART_SELECTED);
    lv_obj_set_style_text_color(point_roller, MAIN_COLOR, LV_PART_SELECTED);
    lv_obj_set_style_text_opa(point_roller, 100, LV_PART_MAIN);
    lv_obj_set_style_text_opa(point_roller, 255, LV_PART_SELECTED);
    lv_obj_set_style_text_line_space(point_roller, 4, LV_PART_MAIN);

    lv_obj_add_event_cb(point_roller, point_roller_handler, LV_EVENT_ALL, NULL);
    lv_roller_set_options(point_roller,
                          "10\n"
                          "20\n"
                          "50\n"
                          "100\n"
                          "200\n"
                          "400",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_selected(point_roller, 3, LV_ANIM_ON);

    lv_obj_t* label2 = lv_label_create(body_obj);
    lv_label_set_text(label2, "Time");
    lv_obj_align_to(label2, point_roller, LV_ALIGN_OUT_TOP_MID, 0, -5);
    lv_obj_set_style_text_color(label2, MAIN_COLOR, LV_PART_MAIN);
    
    // ina226_init();
}

void osc_page_exit(struct page* old_page, struct page* new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_timer_delete(timer);
    MAX_POINT_X = 100;
    is_show_wav = true;
    point_start = MAX_POINT_X;
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
