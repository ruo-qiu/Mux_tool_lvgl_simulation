#include "uart_page.h"

uint8_t            *uart_receiver_buffer;         // 数据存放数组
uint8_t             uart_temp_buffer[10];
lv_style_t uart_style;
lv_obj_t * uart_textarea;
lv_obj_t * uart_send_textarea;
lv_obj_t * uart_ddlist;

lv_obj_t * rx_label, *tx_label;
uint16_t show_charnnum = 0;
uint32_t show_rxnum = 0, show_txnum = 0;

uint8_t uart_get_data;
static lv_obj_t * g_kb_screen;

lv_timer_t * timer1;

static void uart_timer(lv_timer_t * timer)
{
    // uint32_t temp_length = 0;
    // temp_length = fifo_used(&uart_receiver_fifo);
    // if(temp_length == 0)
    // {
    //     return;
    // }
    // if(temp_length > 9)
    // {
    //     temp_length = 9;
    // }
    // show_charnnum += temp_length;
    // if(show_charnnum > 300)
    // {
    //     lv_textarea_set_cursor_pos(uart_textarea, 0);
    //     for(uint8_t i = 0; i < temp_length; i++)
    //     {
    //         lv_textarea_delete_char_forward(uart_textarea);
    //     }
    //     show_charnnum -= temp_length;
    // }
    // fifo_read_buffer(&uart_receiver_fifo, uart_temp_buffer, &temp_length, FIFO_READ_AND_CLEAN);
    // uart_temp_buffer[temp_length] = '\0';
    // lv_textarea_set_cursor_pos(uart_textarea, LV_TEXTAREA_CURSOR_LAST);
    // lv_textarea_add_text(uart_textarea, (const char*)uart_temp_buffer);
    // cdc_send(uart_temp_buffer, temp_length);
    // lv_label_set_text_fmt(rx_label, "%d", show_rxnum);
}
static void kb_screen_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_DEFOCUSED || code == LV_EVENT_LEAVE || code == LV_EVENT_READY)
    {
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_align_to(uart_send_textarea, uart_textarea, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	}
}
__attribute__((unused)) static void ta_screen_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(g_kb_screen, ta);
		lv_obj_move_foreground(g_kb_screen);
        lv_obj_align_to(uart_send_textarea, uart_textarea, LV_ALIGN_TOP_MID, 0, 0);
		lv_obj_clear_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED || code == LV_EVENT_LEAVE)
	{
		lv_keyboard_set_textarea(g_kb_screen, NULL);
        lv_obj_align_to(uart_send_textarea, uart_textarea, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
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


static void send_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if(code == LV_EVENT_CLICKED)
    {
        const char * txt = lv_textarea_get_text(uart_send_textarea);
        // HAL_UART_Transmit(&huart1, (uint8_t *)txt, strlen(txt), 0xffff);
        show_txnum += strlen(txt);
        lv_label_set_text_fmt(tx_label, "%d", show_txnum);
        
//        printf("s = %s\r\n", txt);
	}
}

static void droup_list_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_dropdown_get_selected_str(uart_ddlist, buf, sizeof(buf));
        // printf("Option: %d\n", atoi(buf));
    }
}

static void text_clean_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    if (code == LV_EVENT_LONG_PRESSED)
    {
        lv_textarea_set_text(uart_textarea, "");
        show_txnum = show_rxnum = show_charnnum = 0;
        lv_label_set_text(tx_label, "0");
        lv_label_set_text(rx_label, "0");
    }
}

void uart_text_set_default_style(void)
{
    lv_style_init(&uart_style);
    lv_style_set_bg_color(&uart_style, BACK_COLOR);
    lv_style_set_radius(&uart_style, 5);
    lv_style_set_border_width(&uart_style, 3);
    lv_style_set_border_color(&uart_style, MAIN_COLOR);
    lv_style_set_line_color(&uart_style, MAIN_COLOR);
    lv_style_set_line_opa(&uart_style, 40);
    lv_style_set_text_color(&uart_style, MAIN_COLOR);
    lv_style_set_pad_left(&uart_style, 0);
    lv_style_set_pad_right(&uart_style, 0);
    lv_style_set_pad_top(&uart_style, 5);
    lv_style_set_pad_bottom(&uart_style, 5);
}

void uart_page_init(struct page *page)
{
    uart_text_set_default_style();

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

    timer1 = lv_timer_create(uart_timer, 50,  NULL);

    lv_obj_t * label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "Uart Transmit");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    uart_textarea = lv_textarea_create(body_obj);
    lv_obj_set_size(uart_textarea, 220, 120);
    lv_obj_align(uart_textarea, LV_ALIGN_LEFT_MID, 10, -10);
    lv_obj_add_style(uart_textarea, &uart_style, LV_PART_MAIN);
    lv_textarea_set_max_length(uart_textarea, 300);

    uart_send_textarea = lv_textarea_create(body_obj);
    lv_obj_set_size(uart_send_textarea, 220, 38);
    lv_obj_align_to(uart_send_textarea, uart_textarea, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_add_style(uart_send_textarea, &uart_style, LV_PART_MAIN);
    lv_obj_add_event_cb(uart_send_textarea, ta_screen_event_cb, LV_EVENT_ALL, g_kb_screen);

    // lv_keyboard_set_textarea(g_kb_screen, uart_send_textarea); /*Focus it on one of the text areas to start*/

    uart_ddlist = lv_dropdown_create(body_obj);
	lv_obj_set_size(uart_ddlist, 70, 33);
    lv_obj_align_to(uart_ddlist, uart_textarea, LV_ALIGN_OUT_RIGHT_TOP, 8, 0);
	lv_dropdown_set_options(uart_ddlist, " 9600\n115200\n230400\n460800");
	lv_obj_set_scrollbar_mode(uart_ddlist, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(uart_ddlist, &uart_style, LV_PART_MAIN);
    lv_obj_t * list = lv_dropdown_get_list(uart_ddlist);
    lv_obj_add_style(list, &uart_style, LV_PART_MAIN);
    lv_obj_set_style_bg_color(list, MAIN_COLOR, LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(list, MAIN_COLOR, LV_PART_SELECTED);
    lv_obj_set_style_text_color(list, BACK_COLOR, LV_PART_SELECTED);
    lv_dropdown_set_selected_highlight(uart_ddlist, false);
    lv_obj_set_style_max_height(list, 87, LV_PART_MAIN);
    lv_obj_add_event_cb(uart_ddlist, droup_list_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t * count_obj = lv_btn_create(body_obj);
    lv_obj_set_size(count_obj, 70, 82);
    lv_obj_align_to(count_obj, uart_ddlist, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_add_style(count_obj, &uart_style, LV_PART_MAIN);
    lv_obj_set_style_pad_all(count_obj, 0, 0);
    lv_obj_add_event_cb(count_obj, text_clean_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t * label1 = lv_label_create(count_obj);
    lv_label_set_text(label1, "rx:");
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 2, 2);
    lv_obj_set_style_text_color(label1, MAIN_COLOR, LV_PART_MAIN);

    rx_label = lv_label_create(count_obj);
    lv_label_set_long_mode(rx_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_size(rx_label, 55, 16);
    lv_label_set_text(rx_label, "0");
    lv_obj_align_to(rx_label, label1, LV_ALIGN_OUT_BOTTOM_MID, 20, 2);
    lv_obj_set_style_text_color(rx_label, MAIN_COLOR, LV_PART_MAIN);

    lv_obj_t * label2 = lv_label_create(count_obj);
    lv_label_set_text(label2, "tx:");
    lv_obj_align(label2, LV_ALIGN_TOP_LEFT, 2, 42);
    lv_obj_set_style_text_color(label2, MAIN_COLOR, LV_PART_MAIN);

    tx_label = lv_label_create(count_obj);
    lv_label_set_long_mode(tx_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_size(tx_label, 55, 16);
    lv_label_set_text(tx_label, "0");
    lv_obj_align_to(tx_label, label2, LV_ALIGN_OUT_BOTTOM_MID, 20, 2);
    lv_obj_set_style_text_color(tx_label, MAIN_COLOR, LV_PART_MAIN);

    lv_obj_t * uart_send_btn = lv_btn_create(body_obj);
	lv_obj_set_size(uart_send_btn, 70, 38);
    lv_obj_align_to(uart_send_btn, uart_send_textarea, LV_ALIGN_OUT_RIGHT_MID, 8, 0);
    lv_obj_add_style(uart_send_btn, &uart_style, LV_PART_MAIN);
    lv_obj_t * label3 = lv_label_create(uart_send_btn);
    lv_label_set_text(label3, "Send");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label3, MAIN_COLOR, LV_PART_MAIN);

	lv_obj_add_event_cb(uart_send_btn, send_event_cb, LV_EVENT_ALL, NULL);
    
    uart_receiver_buffer = malloc(400);
    // fifo_init(&uart_receiver_fifo, FIFO_DATA_8BIT, uart_receiver_buffer, 400);
    // HAL_UART_Receive_IT(&huart1, &uart_get_data, 1);
}

void uart_page_exit(struct page *old_page, struct page *new_page)
{
    // fifo_clear(&uart_receiver_fifo);
    free(uart_receiver_buffer);
    lv_timer_delete(timer1);
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
