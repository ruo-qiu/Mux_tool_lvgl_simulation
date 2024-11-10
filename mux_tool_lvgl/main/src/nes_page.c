#include "nes_page.h"

lv_style_t nes_style;
static lv_img_dsc_t nes_img_dsc;
lv_timer_t* nes_timer;
lv_obj_t* nes_img, *nes_list;
uint8_t keyup = 1;
uint8_t keyleft = 2;
uint8_t keyright = 3;
uint8_t keydown = 4;
uint8_t keyA = 5;
uint8_t keyB = 6;
uint8_t keyselect = 7;
uint8_t keystart = 8;

uint8_t keyright_flag = 0;
uint8_t keyleft_flag = 0;
uint8_t keydown_flag = 0;
uint8_t keyup_flag = 0;
uint8_t keystart_flag = 0;
uint8_t keyselect_flag = 0;
uint8_t keyB_flag = 0;
uint8_t keyA_flag = 0;


uint8_t isstart = 0;
uint8_t keysend = 0;

uint8_t key_add_value(uint8_t value)
{

    switch (value)
    {
    case 1:
    {
        keyup_flag = 0x10;
    }break;
    case 2:
    {
        keyleft_flag = 0x40;
    }break;
    case 3:
    {
        keyright_flag = 0x80;
    }break;
    case 4:
    {
        keydown_flag = 0x20;
    }break;
    case 5:
    {
        keyA_flag = 0x01;
    }break;
    case 6:
    {
        keyB_flag = 0x02;
    }break;
    case 7:
    {
        keyselect_flag = 0x04;
    }break;
    case 8:
    {
        keystart_flag = 0x08;
    }break;
    default:
        break;
    }
    keysend = keyright_flag|keyleft_flag|keydown_flag|keyup_flag|keystart_flag|keyselect_flag|keyB_flag|keyA_flag;
    return 0;
}

uint8_t key_clear_value(uint8_t value)
{
//    switch (value)
//    {
//    case 1:
//    {
//        keysend = 0x10;
//    }break;
//    case 2:
//    {
//        keysend = 0x40;
//    }break;
//    case 3:
//    {
//        keysend = 0x80;
//    }break;
//    case 4:
//    {
//        keysend = 0x20;
//    }break;
//    case 5:
//    {
//        keysend = 0x01;
//    }break;
//    case 6:
//    {
//        keysend = 0x02;
//    }break;
//    case 7:
//    {
//        keysend = 0x04;
//    }break;
//    case 8:
//    {
//        keysend = 0x08;
//    }break;
//    default:
//    {
//        keysend = 0;
//    }
//        break;
//    }

    switch (value)
    {
    case 1:
    {
        keyup_flag = 0;
    }break;
    case 2:
    {
        keyleft_flag = 0;
    }break;
    case 3:
    {
        keyright_flag = 0;
    }break;
    case 4:
    {
        keydown_flag = 0;
    }break;
    case 5:
    {
        keyA_flag = 0;
    }break;
    case 6:
    {
        keyB_flag = 0;
    }break;
    case 7:
    {
        keyselect_flag = 0;
    }break;
    case 8:
    {
        keystart_flag = 0;
    }break;
    default:
        break;
    }
    keysend = keyright_flag|keyleft_flag|keydown_flag|keyup_flag|keystart_flag|keyselect_flag|keyB_flag|keyA_flag;
    return 0;
}


static void event_btn_handle(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    uint8_t *key_value = e->user_data;
    if(code == LV_EVENT_PRESSING)   //点击事件
    {
        key_add_value(*key_value);
    }
    if(code == LV_EVENT_RELEASED || code == LV_EVENT_DEFOCUSED || code == LV_EVENT_LEAVE)    //点击事件
    {
        key_clear_value(*key_value);
    }
    // printf("%d\r\n", *key_value);
}

void nes_timer_handle(lv_timer_t* timer)
{
    NesFrameCycle();
    lv_img_set_src(nes_img, &nes_img_dsc);
}

 
static void listbtn1_cb(lv_event_t* event)
{
    nes_main(1);
    lv_obj_clear_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
    nes_timer = lv_timer_create(nes_timer_handle, 16, NULL);
    isstart = 1;
}

static void listbtn2_cb(lv_event_t* event)
{
    nes_main(2);
    lv_obj_clear_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
    nes_timer = lv_timer_create(nes_timer_handle, 16, NULL);
    isstart = 1;
}
static void listbtn3_cb(lv_event_t* event)
{
    nes_main(3);
    lv_obj_clear_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
    nes_timer = lv_timer_create(nes_timer_handle, 16, NULL);
    isstart = 1;
}
static void listbtn4_cb(lv_event_t* event)
{
    nes_main(4);
    lv_obj_clear_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
    nes_timer = lv_timer_create(nes_timer_handle, 16, NULL);
    isstart = 1;
}

static void listbtn5_cb(lv_event_t* event)
{
    nes_main(5);
    lv_obj_clear_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
    nes_timer = lv_timer_create(nes_timer_handle, 16, NULL);
    isstart = 1;
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
    if(code == LV_EVENT_LONG_PRESSED)
    {
        lv_obj_add_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(nes_list, LV_OBJ_FLAG_HIDDEN);
        
        if(isstart)
        {
            lv_timer_delete(nes_timer);
            nes_mem_delete();//释放内存
            isstart = 0;
        }
    }
}


void nes_text_set_default_style(void)
{
    lv_style_init(&nes_style);
    lv_style_set_bg_color(&nes_style, BACK_COLOR);
    lv_style_set_radius(&nes_style, 5);
    lv_style_set_border_width(&nes_style, 3);
    lv_style_set_border_color(&nes_style, MAIN_COLOR);
    lv_style_set_line_color(&nes_style, MAIN_COLOR);
    lv_style_set_line_opa(&nes_style, 40);
    lv_style_set_text_color(&nes_style, MAIN_COLOR);
    lv_style_set_pad_all(&nes_style, 10);
//    lv_style_set_pad_left(&nes_style, 0);
//    lv_style_set_pad_right(&nes_style, 0);
//    lv_style_set_pad_top(&nes_style, 5);
//    lv_style_set_pad_bottom(&nes_style, 5);
}

void nes_page_init(struct page* page)
{
    nes_text_set_default_style();

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
    lv_label_set_text(label0, "NES Game");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);
    
    lv_obj_t* nes_list_obj = lv_obj_create(body_obj);
    lv_obj_add_style(nes_list_obj, &app_style, 0);
    lv_obj_set_size(nes_list_obj, 192, 180);
    lv_obj_align(nes_list_obj, LV_ALIGN_CENTER, 20, 15);

    lv_obj_t* label_list = lv_label_create(nes_list_obj);
    lv_label_set_text(label_list, "game list");
    lv_obj_align(label_list,  LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_color(label_list, BACK_COLOR, LV_PART_MAIN);
    
    nes_list = lv_list_create(nes_list_obj);
    lv_obj_set_size(nes_list, 180, 145);
    lv_obj_align(nes_list, LV_ALIGN_CENTER, 0, 10);
    lv_obj_add_style(nes_list, &app_style, 0);
    lv_obj_t* btn;
    btn = lv_list_add_button(nes_list, LV_SYMBOL_LIST, "Super Mario Bros");
    lv_obj_add_event_cb(btn, listbtn1_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn, &nes_style, 0);
    
    btn = lv_list_add_button(nes_list, LV_SYMBOL_LIST, "War of Tanks");
    lv_obj_add_event_cb(btn, listbtn2_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn, &nes_style, 0);
    
    btn = lv_list_add_button(nes_list, LV_SYMBOL_LIST, "AnQi");
    lv_obj_add_event_cb(btn, listbtn3_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn, &nes_style, 0);
    
    btn = lv_list_add_button(nes_list, LV_SYMBOL_LIST, "Mario, plumber");
    lv_obj_add_event_cb(btn, listbtn4_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn, &nes_style, 0);
    
    btn = lv_list_add_button(nes_list, LV_SYMBOL_LIST, "Balloon Fight");
    lv_obj_add_event_cb(btn, listbtn5_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn, &nes_style, 0);
    

    nes_img = lv_img_create(body_obj);
    lv_obj_add_style(nes_img, &nes_style, 0);
    lv_obj_set_size(nes_img, 192, 180);
    lv_obj_align(nes_img, LV_ALIGN_CENTER, 20, 15);
    lv_image_set_scale_x(nes_img, 192);
    lv_image_set_scale_y(nes_img, 192);
    nes_img_dsc.header.cf = LV_COLOR_FORMAT_RGB565;
    nes_img_dsc.data = (uint8_t*)show_img;
    nes_img_dsc.header.w = 256;
    nes_img_dsc.header.h = 240;
    lv_obj_add_flag(nes_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_t * nes_up_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_up_btn, &nes_style, 0);
    lv_obj_set_size(nes_up_btn, 40, 40);
    lv_obj_align(nes_up_btn, LV_ALIGN_BOTTOM_LEFT, 20, -130);
    lv_obj_t* label1 = lv_label_create(nes_up_btn);
    lv_label_set_text(label1, LV_SYMBOL_UP);
    lv_obj_align(label1,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label1, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_up_btn, event_btn_handle, LV_EVENT_ALL, &keyup);
    
    lv_obj_t * nes_left_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_left_btn, &nes_style, 0);
    lv_obj_set_size(nes_left_btn, 40, 40);
    lv_obj_align(nes_left_btn, LV_ALIGN_BOTTOM_LEFT, 00, -90);
    lv_obj_t* label2 = lv_label_create(nes_left_btn);
    lv_label_set_text(label2, LV_SYMBOL_LEFT);
    lv_obj_align(label2,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label2, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_left_btn, event_btn_handle, LV_EVENT_ALL, &keyleft);
    
    lv_obj_t * nes_right_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_right_btn, &nes_style, 0);
    lv_obj_set_size(nes_right_btn, 40, 40);
    lv_obj_align(nes_right_btn, LV_ALIGN_BOTTOM_LEFT, 40, -90);
    lv_obj_t* label3 = lv_label_create(nes_right_btn);
    lv_label_set_text(label3, LV_SYMBOL_RIGHT);
    lv_obj_align(label3,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label3, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_right_btn, event_btn_handle, LV_EVENT_ALL, &keyright);
    
    lv_obj_t * nes_down_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_down_btn, &nes_style, 0);
    lv_obj_set_size(nes_down_btn, 40, 40);
    lv_obj_align(nes_down_btn, LV_ALIGN_BOTTOM_LEFT, 20, -50);
    lv_obj_t* label4 = lv_label_create(nes_down_btn);
    lv_label_set_text(label4, LV_SYMBOL_DOWN);
    lv_obj_align(label4,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label4, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_down_btn, event_btn_handle, LV_EVENT_ALL, &keydown);

    
    lv_obj_t * nes_A_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_A_btn, &nes_style, 0);
    lv_obj_set_size(nes_A_btn, 40, 40);
    lv_obj_align(nes_A_btn, LV_ALIGN_BOTTOM_RIGHT, -0, -115);
    lv_obj_t* label5 = lv_label_create(nes_A_btn);
    lv_label_set_text(label5, "A");
    lv_obj_align(label5,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label5, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_A_btn, event_btn_handle, LV_EVENT_ALL, &keyA);
    
    lv_obj_t * nes_B_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_B_btn, &nes_style, 0);
    lv_obj_set_size(nes_B_btn, 40, 40);
    lv_obj_align(nes_B_btn, LV_ALIGN_BOTTOM_RIGHT, -0, -65);
    lv_obj_t* label6 = lv_label_create(nes_B_btn);
    lv_label_set_text(label6, "B");
    lv_obj_align(label6,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label6, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_B_btn, event_btn_handle, LV_EVENT_ALL, &keyB);


    lv_obj_t * nes_select_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_select_btn, &nes_style, 0);
    lv_obj_set_size(nes_select_btn, 40, 40);
    lv_obj_align(nes_select_btn, LV_ALIGN_BOTTOM_RIGHT, -0, -0);
    lv_obj_t* label7 = lv_label_create(nes_select_btn);
    lv_label_set_text(label7, LV_SYMBOL_OK);
    lv_obj_align(label7,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label7, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_select_btn, event_btn_handle, LV_EVENT_ALL, &keyselect);
    
    lv_obj_t * nes_start_btn = lv_button_create(body_obj);
    lv_obj_add_style(nes_start_btn, &nes_style, 0);
    lv_obj_set_size(nes_start_btn, 40, 40);
    lv_obj_align(nes_start_btn, LV_ALIGN_BOTTOM_LEFT, 20, -0);
    lv_obj_t* label8 = lv_label_create(nes_start_btn);
    lv_label_set_text(label8, LV_SYMBOL_PLAY);
    lv_obj_align(label8,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label8, MAIN_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb(nes_start_btn, event_btn_handle, LV_EVENT_ALL, &keystart);
    isstart = 0;
}

void nes_page_exit(struct page* old_page, struct page* new_page)
{
    lv_obj_clean(old_page->body_obj);
    if(isstart)
    {
        nes_mem_delete();//释放内存
        lv_timer_delete(nes_timer);
    }
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
