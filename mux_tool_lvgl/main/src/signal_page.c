#include "signal_page.h"

lv_style_t signal_style;
lv_obj_t * label_freq_value;
lv_obj_t * label_duty_value;
lv_obj_t * signal_trian_btn;
lv_obj_t * signal_rectan_btn;
lv_obj_t * signal_sine_btn;
lv_obj_t * signal_servo_btn;

uint8_t trian_flag = 0, rectan_flag = 0, sine_flag = 0, servo_flag = 0;
static void trian_btn_event_cb(lv_event_t * e)
{
    trian_flag = !trian_flag;
    if(trian_flag)
    {
        rectan_flag = sine_flag = servo_flag = 0;
        lv_obj_set_style_bg_color(signal_trian_btn, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_trian_btn, 0), BACK_COLOR, LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(signal_trian_btn, BACK_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_trian_btn, 0), MAIN_COLOR, LV_PART_MAIN);
    }

    lv_obj_set_style_bg_color(signal_rectan_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_rectan_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_sine_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_sine_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_servo_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_servo_btn, 0), MAIN_COLOR, LV_PART_MAIN);
}
static void rect_btn_event_cb(lv_event_t * e)
{
    rectan_flag = !rectan_flag;
    lv_obj_set_style_bg_color(signal_trian_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_trian_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    if(rectan_flag)
    {
        trian_flag = sine_flag = servo_flag = 0;
        lv_obj_set_style_bg_color(signal_rectan_btn, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_rectan_btn, 0), BACK_COLOR, LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(signal_rectan_btn, BACK_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_rectan_btn, 0), MAIN_COLOR, LV_PART_MAIN);
    }

    lv_obj_set_style_bg_color(signal_sine_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_sine_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_servo_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_servo_btn, 0), MAIN_COLOR, LV_PART_MAIN);
}
static void sine_btn_event_cb(lv_event_t * e)
{
    sine_flag = !sine_flag;
    lv_obj_set_style_bg_color(signal_trian_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_trian_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_rectan_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_rectan_btn, 0), MAIN_COLOR, LV_PART_MAIN);
    if(sine_flag)
    {
        rectan_flag = trian_flag = servo_flag = 0;
        lv_obj_set_style_bg_color(signal_sine_btn, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_sine_btn, 0), BACK_COLOR, LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(signal_sine_btn, BACK_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_sine_btn, 0), MAIN_COLOR, LV_PART_MAIN);
    }

    lv_obj_set_style_bg_color(signal_servo_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_servo_btn, 0), MAIN_COLOR, LV_PART_MAIN);
}
static void servo_btn_event_cb(lv_event_t * e)
{
    servo_flag = !servo_flag;
    lv_obj_set_style_bg_color(signal_trian_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_trian_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_rectan_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_rectan_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(signal_sine_btn, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_obj_get_child(signal_sine_btn, 0), MAIN_COLOR, LV_PART_MAIN);

    if(servo_flag)
    {
        rectan_flag = trian_flag = sine_flag = 0;
        lv_obj_set_style_bg_color(signal_servo_btn, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_servo_btn, 0), BACK_COLOR, LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(signal_servo_btn, BACK_COLOR, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(signal_servo_btn, 0), MAIN_COLOR, LV_PART_MAIN);
    }
}

static void freq_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%dkHz", (int)lv_slider_get_value(slider));
    lv_label_set_text(label_freq_value, buf);
    lv_obj_align_to(label_freq_value, slider, LV_ALIGN_OUT_TOP_RIGHT, 0, -10);
}

static void duty_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(label_duty_value, buf);
    lv_obj_align_to(label_duty_value, slider, LV_ALIGN_OUT_TOP_RIGHT, 0, -10);
}

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


void signal_text_set_default_style(void)
{
    lv_style_init(&signal_style);
    lv_style_set_bg_color(&signal_style, BACK_COLOR);
    lv_style_set_radius(&signal_style, 5);
    lv_style_set_border_width(&signal_style, 3);
    lv_style_set_border_color(&signal_style, MAIN_COLOR);
    lv_style_set_line_color(&signal_style, MAIN_COLOR);
    lv_style_set_line_opa(&signal_style, 40);
    lv_style_set_text_color(&signal_style, MAIN_COLOR);
    lv_style_set_pad_left(&signal_style, 0);
    lv_style_set_pad_right(&signal_style, 0);
    lv_style_set_pad_top(&signal_style, 5);
    lv_style_set_pad_bottom(&signal_style, 5);
}


void signal_page_init(struct page *page)
{
    signal_text_set_default_style();
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
    lv_label_set_text(label0, "Signal Generator");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    signal_trian_btn = lv_btn_create(body_obj);
	lv_obj_set_size(signal_trian_btn, 60, 80);
    lv_obj_align(signal_trian_btn, LV_ALIGN_LEFT_MID, 22, -35);
    lv_obj_add_style(signal_trian_btn, &signal_style, LV_PART_MAIN);
    lv_obj_t * label_trian = lv_label_create(signal_trian_btn);
    lv_label_set_text(label_trian, "trian\nwave\n  /\\/\\");
    lv_obj_align(label_trian, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label_trian, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(signal_trian_btn, trian_btn_event_cb, LV_EVENT_CLICKED, NULL);

    signal_rectan_btn = lv_btn_create(body_obj);
	lv_obj_set_size(signal_rectan_btn, 60, 80);
    lv_obj_align(signal_rectan_btn, LV_ALIGN_LEFT_MID, 94, -35);
    lv_obj_add_style(signal_rectan_btn, &signal_style, LV_PART_MAIN);
    lv_obj_t * label_rectan = lv_label_create(signal_rectan_btn);
    lv_label_set_text(label_rectan, " rect\nwave\n _|-|_");
    lv_obj_align(label_rectan, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label_rectan, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(signal_rectan_btn, rect_btn_event_cb, LV_EVENT_CLICKED, NULL);
    
    signal_sine_btn = lv_btn_create(body_obj);
	lv_obj_set_size(signal_sine_btn, 60, 80);
    lv_obj_align(signal_sine_btn, LV_ALIGN_LEFT_MID, 166, -35);
    lv_obj_add_style(signal_sine_btn, &signal_style, LV_PART_MAIN);
    lv_obj_t * label_sine = lv_label_create(signal_sine_btn);
    lv_label_set_text(label_sine, " sine\nwave\n  ~~~");
    lv_obj_align(label_sine, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label_sine, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(signal_sine_btn, sine_btn_event_cb, LV_EVENT_CLICKED, NULL);
    
    signal_servo_btn = lv_btn_create(body_obj);
	lv_obj_set_size(signal_servo_btn, 60, 80);
    lv_obj_align(signal_servo_btn, LV_ALIGN_LEFT_MID, 238, -35);
    lv_obj_add_style(signal_servo_btn, &signal_style, LV_PART_MAIN);
    lv_obj_t * label_servo = lv_label_create(signal_servo_btn);
    lv_label_set_text(label_servo, "servo\nwave\n  <->");
    lv_obj_align(label_servo, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label_servo, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(signal_servo_btn, servo_btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * freq_slider = lv_slider_create(body_obj);
	lv_obj_set_size(freq_slider, 270, 12);
    lv_obj_align(freq_slider, LV_ALIGN_CENTER, 0, 45);
    lv_obj_set_style_bg_color(freq_slider, MAIN_COLOR, LV_PART_KNOB);
    lv_obj_set_style_bg_color(freq_slider, MAIN_COLOR, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(freq_slider, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_border_width(freq_slider, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(freq_slider, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label_freq = lv_label_create(body_obj);
    lv_label_set_text(label_freq, "freq (kHz)");
    lv_obj_align_to(label_freq, freq_slider, LV_ALIGN_OUT_TOP_LEFT, 0, -10);
    lv_obj_set_style_text_color(label_freq, MAIN_COLOR, LV_PART_MAIN);
    label_freq_value = lv_label_create(body_obj);
    lv_label_set_text(label_freq_value, "0kHz");
    lv_obj_align_to(label_freq_value, freq_slider, LV_ALIGN_OUT_TOP_RIGHT, 0, -10);
    lv_obj_set_style_text_color(label_freq_value, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(freq_slider, freq_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
    lv_obj_t * duty_slider = lv_slider_create(body_obj);
	lv_obj_set_size(duty_slider, 270, 12);
    lv_obj_align(duty_slider, LV_ALIGN_CENTER, 0, 90);
    lv_obj_set_style_bg_color(duty_slider, MAIN_COLOR, LV_PART_KNOB);
    lv_obj_set_style_bg_color(duty_slider, MAIN_COLOR, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(duty_slider, BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_border_width(duty_slider, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(duty_slider, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label_duty = lv_label_create(body_obj);
    lv_label_set_text(label_duty, "duty (%)");
    lv_obj_align_to(label_duty, duty_slider, LV_ALIGN_OUT_TOP_LEFT, 0, -10);
    lv_obj_set_style_text_color(label_duty, MAIN_COLOR, LV_PART_MAIN);
    label_duty_value = lv_label_create(body_obj);
    lv_label_set_text(label_duty_value, "0%%");
    lv_obj_align_to(label_duty_value, duty_slider, LV_ALIGN_OUT_TOP_RIGHT, 0, -10);
    lv_obj_set_style_text_color(label_duty_value, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(duty_slider, duty_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

}


void signal_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
