#include "enter_page.h"
#define ENTER_LIST_NUM 10
enter_struct enter_list[ENTER_LIST_NUM];
enter_struct quick_list[ENTER_LIST_NUM];
enter_struct website_list[ENTER_LIST_NUM];
lv_style_t enter_style;
lv_obj_t *enter_bg_obj, *quick_bg_obj, *website_bg_obj;
lv_obj_t *enter_body_obj;
lv_obj_t * enter_tabview;
lv_obj_t * enter_tab1;
lv_obj_t * enter_tab2;
lv_obj_t * enter_tab3;


void event_enter_list_btn_handler(lv_event_t* e)
{
    uint16_t *key_value = e->user_data;
//    printf("key:%d\r\n", *key_value);
//    printf("account:%s\r\n", enter_list[*key_value].enter_account);
//    printf("enter_password:%s\r\n", enter_list[*key_value].enter_password);
    // if(enter_list[*key_value].enter_account[0] != ' ')
    // {
    //     keyboard_send_str(enter_list[*key_value].enter_account);
    //     keyboard_send(0, 0x2B);
    // }
    // keyboard_send_str(enter_list[*key_value].enter_password);
    // keyboard_send(0, 0x28);
}


void event_quick_btn_handler(lv_event_t* e)
{
    // uint16_t *key_value = e->user_data;
    
    // keyboard_send(8, 0x15); //win+r
    // keyboard_send_str("cmd");
    // keyboard_send(0, 0x28);
    // HAL_Delay(50);
    // if(quick_list[*key_value].enter_account[0] != ' ')
    // {
    //     keyboard_send_str(quick_list[*key_value].enter_account);
    //     keyboard_send(0, 0x28);
    // }
    // HAL_Delay(50);
    // if(quick_list[*key_value].enter_password[0] != ' ')
    // {
    //     keyboard_send_str(quick_list[*key_value].enter_password);
    //     keyboard_send(0, 0x28);
    // }
    
//    printf("key:%d\r\n", *key_value);
//    if(quick_list[*key_value].enter_account[0] != ' ')
//    {
//        printf("account:%s\r\n", quick_list[*key_value].enter_account);
//    }
//    printf("enter_password:%s\r\n", quick_list[*key_value].enter_password);
}

void event_website_btn_handler(lv_event_t* e)
{
    // uint16_t *key_value = e->user_data;
    // keyboard_send(8, 0x15); //win+r
    // keyboard_send_str(website_list[*key_value].enter_password);
    // keyboard_send(0, 0x28);
//    printf("key:%d\r\n", *key_value);
//    if(website_list[*key_value].enter_account[0] != ' ')
//    {
//        printf("account:%s\r\n", website_list[*key_value].enter_account);
//    }
//    printf("enter_password:%s\r\n", website_list[*key_value].enter_password);
}

void event_add_btn_handler(lv_event_t* e)
{
    enter_list_add(enter_bg_obj, "name", "account", "password");
    create_enter_list_to_page(enter_bg_obj);
    lv_obj_scroll_to_view(lv_obj_get_child(enter_bg_obj, -1), LV_ANIM_OFF);
}
void enter_list_init()
{
    uint16_t i = 0;
    for (i = 0; i < ENTER_LIST_NUM; i++)
    {
        enter_list[i].enter_num = 65535;
        enter_list[i].enter_btn = NULL;
        memset(enter_list[i].enter_name, 0, sizeof(enter_list[i].enter_name));
        memset(enter_list[i].enter_account, 0, sizeof(enter_list[i].enter_account));
        memset(enter_list[i].enter_password, 0, sizeof(enter_list[i].enter_password));
    
        quick_list[i].enter_num = 65535;
        quick_list[i].enter_btn = NULL;
        memset(quick_list[i].enter_name, 0, sizeof(quick_list[i].enter_name));
        memset(quick_list[i].enter_account, 0, sizeof(quick_list[i].enter_account));
        memset(quick_list[i].enter_password, 0, sizeof(quick_list[i].enter_password));

        website_list[i].enter_num = 65535;
        website_list[i].enter_btn = NULL;
        memset(website_list[i].enter_name, 0, sizeof(website_list[i].enter_name));
        memset(website_list[i].enter_account, 0, sizeof(website_list[i].enter_account));
        memset(website_list[i].enter_password, 0, sizeof(website_list[i].enter_password));
    }
}

void enter_list_add(lv_obj_t *parent_obj, char *name, char *account, char* password)
{
    uint16_t i = 0;
    for (i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(enter_list[i].enter_num == 65535)
        {
            break;
        }
    }
    if(i == ENTER_LIST_NUM)
    {
        return;
    }
    enter_list[i].enter_num = i;
    memcpy(enter_list[i].enter_name, name, strlen(name));
    memcpy(enter_list[i].enter_account, account, strlen(account));
    memcpy(enter_list[i].enter_password, password, strlen(password));
}

void quick_list_add(lv_obj_t *parent_obj, char *name, char *account, char* password)
{
    uint16_t i = 0;
    for (i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(quick_list[i].enter_num == 65535)
        {
            break;
        }
    }
    if(i == ENTER_LIST_NUM)
    {
        return;
    }
    quick_list[i].enter_num = i;
    memcpy(quick_list[i].enter_name, name, strlen(name));
    memcpy(quick_list[i].enter_account, account, strlen(account));
    memcpy(quick_list[i].enter_password, password, strlen(password));
}

void website_list_add(lv_obj_t *parent_obj, char *name, char *account, char* password)
{
    uint16_t i = 0;
    for (i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(website_list[i].enter_num == 65535)
        {
            break;
        }
    }
    if(i == ENTER_LIST_NUM)
    {
        return;
    }
    website_list[i].enter_num = i;
    memcpy(website_list[i].enter_name, name, strlen(name));
    memcpy(website_list[i].enter_account, account, strlen(account));
    memcpy(website_list[i].enter_password, password, strlen(password));
}

void create_enter_list_to_page(lv_obj_t *parent_obj)
{
    uint16_t i = 0;
    int page_width = lv_obj_get_width(parent_obj);
    lv_obj_clean(parent_obj);
    for(i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(enter_list[i].enter_num == 65535)
        {
            break;
        }
        enter_list[i].enter_btn = lv_btn_create(parent_obj);
        lv_obj_add_style(enter_list[i].enter_btn, &enter_style, 0);
        lv_obj_set_size(enter_list[i].enter_btn, page_width  / 2.3, (page_width / 8));
        lv_obj_set_pos(enter_list[i].enter_btn, (i % 2) * (page_width / 2.5 + 20) + 15, (int)((i / 2) * (page_width / 6) + 20));
        lv_obj_add_event_cb(enter_list[i].enter_btn, event_enter_list_btn_handler, LV_EVENT_CLICKED, &enter_list[i].enter_num);

        lv_obj_t * enter_label = lv_label_create(enter_list[i].enter_btn);
        lv_label_set_text_fmt(enter_label, "%d: %s",enter_list[i].enter_num, enter_list[i].enter_name);
        lv_obj_set_style_text_color(enter_label, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_align(enter_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_update_layout(enter_list[i].enter_btn);
        lv_obj_update_layout(enter_label);
    }
}

void create_quick_list_to_page(lv_obj_t *parent_obj)
{
    uint16_t i = 0;
    int page_width = lv_obj_get_width(parent_obj);
    lv_obj_clean(parent_obj);
    for(i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(quick_list[i].enter_num == 65535)
        {
            break;
        }
        // lv_obj_add_event_cb(app_admin[i].btn, app_admin[i].callback, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
        quick_list[i].enter_btn = lv_btn_create(parent_obj);
        lv_obj_add_style(quick_list[i].enter_btn, &enter_style, 0);

        lv_obj_set_size(quick_list[i].enter_btn, page_width  / 2.3, (page_width / 8));
        lv_obj_set_pos(quick_list[i].enter_btn, (i % 2) * (page_width / 2.5 + 30) + 8, (int)((i / 2) * (page_width / 6) + 30));
        lv_obj_add_event_cb(quick_list[i].enter_btn, event_quick_btn_handler, LV_EVENT_CLICKED, &quick_list[i].enter_num);

        lv_obj_t * enter_label = lv_label_create(quick_list[i].enter_btn);
        lv_label_set_text_fmt(enter_label, "%d: %s",quick_list[i].enter_num, quick_list[i].enter_name);
        lv_obj_set_style_text_color(enter_label, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_align(enter_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_update_layout(quick_list[i].enter_btn);
        lv_obj_update_layout(enter_label);
    }
}

void create_website_list_to_page(lv_obj_t *parent_obj)
{
    uint16_t i = 0;
    int page_width = lv_obj_get_width(parent_obj);
    lv_obj_clean(parent_obj);
    for(i = 0; i < ENTER_LIST_NUM; i++)
    {
        if(website_list[i].enter_num == 65535)
        {
            break;
        }
        // lv_obj_add_event_cb(app_admin[i].btn, app_admin[i].callback, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
        website_list[i].enter_btn = lv_btn_create(parent_obj);
        lv_obj_add_style(website_list[i].enter_btn, &enter_style, 0);

        lv_obj_set_size(website_list[i].enter_btn, page_width  / 2.3, (page_width / 8));
        lv_obj_set_pos(website_list[i].enter_btn, (i % 2) * (page_width / 2.5 + 30) + 8, (int)((i / 2) * (page_width / 6) + 30));
        lv_obj_add_event_cb(website_list[i].enter_btn, event_website_btn_handler, LV_EVENT_CLICKED, &website_list[i].enter_num);

        lv_obj_t * enter_label = lv_label_create(website_list[i].enter_btn);
        lv_label_set_text_fmt(enter_label, "%d: %s",website_list[i].enter_num, website_list[i].enter_name);
        lv_obj_set_style_text_color(enter_label, MAIN_COLOR, LV_PART_MAIN);
        lv_obj_align(enter_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_update_layout(website_list[i].enter_btn);
        lv_obj_update_layout(enter_label);
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
    if(code == LV_EVENT_LONG_PRESSED)    //点击事件
    {
        page_transition_to_page_name("usbmk_page");
    }
}


void enter_text_set_default_style(void)
{
    lv_style_init(&enter_style);
    lv_style_set_bg_color(&enter_style, BACK_COLOR);
    lv_style_set_radius(&enter_style, 5);
    lv_style_set_border_width(&enter_style, 3);
    lv_style_set_border_color(&enter_style, MAIN_COLOR);
    lv_style_set_line_color(&enter_style, MAIN_COLOR);
    lv_style_set_line_opa(&enter_style, 40);
    lv_style_set_text_color(&enter_style, MAIN_COLOR);
    lv_style_set_pad_left(&enter_style, 10);
    lv_style_set_pad_right(&enter_style, 10);
    lv_style_set_pad_top(&enter_style, 5);
    lv_style_set_pad_bottom(&enter_style, 5);
}

void enter_page_init(struct page *page)
{
    enter_text_set_default_style();
    enter_list_init();
    enter_body_obj = page->body_obj;

    lv_obj_t * top_obj = lv_obj_create(enter_body_obj);
    lv_obj_add_event_cb(top_obj, event_top_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
    lv_obj_add_style(top_obj, &app_style, 0);
    lv_obj_set_size(top_obj, lv_obj_get_width(enter_body_obj), 25);
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
    lv_label_set_text(label0, "Enter Ctrl");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);
    
    enter_tabview = lv_tabview_create(enter_body_obj);
    lv_obj_set_size(enter_tabview, lv_obj_get_width(enter_body_obj), lv_obj_get_height(enter_body_obj) - 25);
    lv_obj_set_pos(enter_tabview, 0, 25);
    lv_obj_set_style_bg_color(enter_tabview, BACK_COLOR, 0);
    lv_obj_set_style_bg_color(lv_tabview_get_tab_bar(enter_tabview), BACK_COLOR, LV_PART_MAIN);
    lv_obj_set_style_border_color(lv_tabview_get_tab_bar(enter_tabview), MAIN_COLOR, LV_PART_MAIN);
    lv_obj_set_style_border_width(lv_tabview_get_tab_bar(enter_tabview), 3, LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_tabview_get_tab_bar(enter_tabview), MAIN_COLOR, LV_PART_MAIN);


    lv_obj_set_style_pad_all(enter_tabview, 0, LV_PART_MAIN);
    lv_tabview_set_tab_bar_position(enter_tabview, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(enter_tabview, 30);
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    enter_tab1 = lv_tabview_add_tab(enter_tabview, "Account");
    enter_tab2 = lv_tabview_add_tab(enter_tabview, "Quick");
    enter_tab3 = lv_tabview_add_tab(enter_tabview, "Website");
    lv_obj_clear_flag(enter_tab1, LV_OBJ_FLAG_SCROLLABLE);  
    lv_obj_clear_flag(enter_tab2, LV_OBJ_FLAG_SCROLLABLE);  
    lv_obj_clear_flag(enter_tab3, LV_OBJ_FLAG_SCROLLABLE);  

    lv_theme_default_init(NULL, MAIN_COLOR, BACK_COLOR, LV_THEME_DEFAULT_DARK, &lv_font_montserrat_14);
    
    enter_bg_obj = lv_obj_create(enter_tab1);
    lv_obj_set_size(enter_bg_obj, lv_obj_get_width(enter_tab1)-0, lv_obj_get_height(enter_body_obj) - 50);
    lv_obj_center(enter_bg_obj);
    lv_obj_add_style(enter_bg_obj, &page_style, 0);
    lv_obj_set_style_pad_all(enter_bg_obj, 0, LV_PART_MAIN);
    lv_obj_update_layout(enter_bg_obj);  

    quick_bg_obj = lv_obj_create(enter_tab2);
    lv_obj_set_size(quick_bg_obj, lv_obj_get_width(enter_tab2)-0, lv_obj_get_height(enter_body_obj) - 50);
    lv_obj_center(quick_bg_obj);
    lv_obj_add_style(quick_bg_obj, &page_style, 0);
    lv_obj_set_style_pad_all(quick_bg_obj, 0, LV_PART_MAIN);
    lv_obj_update_layout(quick_bg_obj);  

    website_bg_obj = lv_obj_create(enter_tab3);
    lv_obj_set_size(website_bg_obj, lv_obj_get_width(enter_tab3)-0, lv_obj_get_height(enter_body_obj) - 50);
    lv_obj_center(website_bg_obj);
    lv_obj_add_style(website_bg_obj, &page_style, 0);
    lv_obj_set_style_pad_all(website_bg_obj, 0, LV_PART_MAIN);
    lv_obj_update_layout(website_bg_obj);  

    enter_list_add(enter_bg_obj, "QQ", "0", "0");
    enter_list_add(enter_bg_obj, "Steam", "0", "0");
    enter_list_add(enter_bg_obj, "Gitee", "0", "0");
    enter_list_add(enter_bg_obj, "Windows", " ", "0");
    enter_list_add(enter_bg_obj, "Nexusmods", "0", "0");
    enter_list_add(enter_bg_obj, "CSDN", "0", "0");
    enter_list_add(enter_bg_obj, "Github", "0", "0");
    enter_list_add(enter_bg_obj, "JlcEDA", "0", "0");
    enter_list_add(enter_bg_obj, "Bilibili", "0", "0");
    create_enter_list_to_page(enter_bg_obj);

    quick_list_add(quick_bg_obj, "WuKong", "game", "3");
    create_quick_list_to_page(quick_bg_obj);

    website_list_add(website_bg_obj, "Wu_Map", " ", "https://www.gamersky.com/tools/map/wukong/?mapId=61");
    create_website_list_to_page(website_bg_obj);
}


void enter_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
