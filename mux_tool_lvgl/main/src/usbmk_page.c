#include "usbmk_page.h"

lv_style_t usbmk_style;
lv_obj_t * usbmk_textarea;
lv_obj_t * usbmk_send_textarea;

static lv_obj_t * g_kb_screen;
static void kb_screen_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_DEFOCUSED || code == LV_EVENT_LEAVE || code == LV_EVENT_READY)
    {
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
__attribute__((unused)) static void ta_screen_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = NULL;
	if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(g_kb_screen, ta);
		lv_obj_move_foreground(g_kb_screen);
		lv_obj_clear_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED || code == LV_EVENT_LEAVE || code == LV_EVENT_READY)
	{
		lv_keyboard_set_textarea(g_kb_screen, NULL);
		lv_obj_move_background(g_kb_screen);
		lv_obj_add_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	}
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

uint8_t move_flag = false, long_press = false;
uint16_t move_dis = 0;
static void mouse_move_handler(lv_event_t* e)
{
    // lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    // lv_indev_t* indev = lv_indev_get_act(); //获取输入设备
	// if (indev == NULL)  return;
    // lv_point_t vect;
    // lv_indev_get_vect(indev, &vect);
    
    // if (code == LV_EVENT_PRESSING ) 
    // {
    //     if(!move_flag)
    //     {
    //         move_flag = true;
    //     }
    //     if(move_flag)
    //     {   
    //         move_dis += vect.x*2 + vect.y*2;
    //     }
    //     mouse_send(0, vect.x*2, vect.y*2);
    // }
    // if(code == LV_EVENT_CLICKED)
    // {
    //     if(move_dis < 2)
    //     {
    //         if(long_press)
    //         {
    //             mouse_send(2, 0, 0);
    //             HAL_Delay(10);
    //             mouse_send(0, 0, 0);
    //         }
    //         else
    //         {
    //             mouse_send(1, 0, 0);
    //             HAL_Delay(5);
    //             mouse_send(0, 0, 0);
    //         }
    //     }
    //     move_dis = 0;
    //     move_flag = false;
    //     long_press = false;
    // }
    // if(code == LV_EVENT_LONG_PRESSED)
    // {
    //     long_press = true;
    // }
}

void usbmk_text_set_default_style(void)
{
    lv_style_init(&usbmk_style);
    lv_style_set_bg_color(&usbmk_style, BACK_COLOR);
    lv_style_set_radius(&usbmk_style, 5);
    lv_style_set_border_width(&usbmk_style, 3);
    lv_style_set_border_color(&usbmk_style, MAIN_COLOR);
    lv_style_set_line_color(&usbmk_style, MAIN_COLOR);
    lv_style_set_line_opa(&usbmk_style, 40);
    lv_style_set_text_color(&usbmk_style, MAIN_COLOR);
    lv_style_set_pad_left(&usbmk_style, 0);
    lv_style_set_pad_right(&usbmk_style, 0);
    lv_style_set_pad_top(&usbmk_style, 5);
    lv_style_set_pad_bottom(&usbmk_style, 5);
}

void usbmk_page_init(struct page *page)
{
    usbmk_text_set_default_style();

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

	g_kb_screen = lv_keyboard_create(body_obj);
    lv_obj_set_size(g_kb_screen,  LV_HOR_RES, LV_VER_RES / 2);
    lv_obj_add_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_event_cb(g_kb_screen, kb_screen_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(g_kb_screen, MAIN_COLOR, LV_PART_MAIN);
    // lv_obj_add_style(g_kb_screen, &app_style, 0);
    lv_keyboard_set_popovers(g_kb_screen, true);

    lv_obj_t * label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "Usbmk Ctrl");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    lv_obj_t * mouse_obj = lv_obj_create(body_obj);
    lv_obj_add_event_cb(mouse_obj, mouse_move_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
    lv_obj_add_style(mouse_obj, &usbmk_style, 0);
    lv_obj_set_size(mouse_obj, 240, 185);
    lv_obj_align(mouse_obj, LV_ALIGN_CENTER, -25, 13);


    lv_obj_t * usbmk_left_btn = lv_btn_create(body_obj);
	lv_obj_set_size(usbmk_left_btn, 50, 38);
    lv_obj_align(usbmk_left_btn, LV_ALIGN_TOP_RIGHT, 0, 40);
    lv_obj_set_style_bg_color(usbmk_left_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label1 = lv_label_create(usbmk_left_btn);
    lv_label_set_text(label1, "left");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label1, BACK_COLOR, LV_PART_MAIN);


    lv_obj_t * usbmk_mid_btn = lv_btn_create(body_obj);
	lv_obj_set_size(usbmk_mid_btn, 50, 38);
    lv_obj_align(usbmk_mid_btn, LV_ALIGN_TOP_RIGHT, 0, 78 + 10);
    lv_obj_set_style_bg_color(usbmk_mid_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label2 = lv_label_create(usbmk_mid_btn);
    lv_label_set_text(label2, "mid");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label2, BACK_COLOR, LV_PART_MAIN);

    lv_obj_t * usbmk_right_btn = lv_btn_create(body_obj);
	lv_obj_set_size(usbmk_right_btn, 50, 38);
    lv_obj_align(usbmk_right_btn, LV_ALIGN_TOP_RIGHT, 0, 118 + 20);
    lv_obj_set_style_bg_color(usbmk_right_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label3 = lv_label_create(usbmk_right_btn);
    lv_label_set_text(label3, "right");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label3, BACK_COLOR, LV_PART_MAIN);

    lv_obj_t * usbmk_keyboard_btn = lv_btn_create(body_obj);
	lv_obj_set_size(usbmk_keyboard_btn, 50, 38);
    lv_obj_align(usbmk_keyboard_btn, LV_ALIGN_TOP_RIGHT, 0, 158 + 30);
    lv_obj_set_style_bg_color(usbmk_keyboard_btn, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_t * label4 = lv_label_create(usbmk_keyboard_btn);
    lv_label_set_text(label4, "keyb");
    lv_obj_align(label4, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label4, BACK_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(usbmk_keyboard_btn, ta_screen_event_cb, LV_EVENT_ALL, g_kb_screen);
}

void usbmk_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
